package main

import (
	"context"
	"errors"
	"flag"
	"fmt"
	"log"
	"net"
	"net/http"
	"net/http/httputil"
	"net/url"
	"strings"
	"sync"
	"sync/atomic"
	"time"
)

// Idea from this article: `https://kasvith.me/posts/lets-create-a-simple-lb-go/`.

type Server struct {
	Aliveness    bool
	mu           sync.RWMutex
	URL          *url.URL
	ReverseProxy *httputil.ReverseProxy
}

func (s *Server) SetAlive(enable bool) {
	s.mu.Lock()
	s.Aliveness = enable
	s.mu.Unlock()
}

func (s *Server) IsAlive() (status bool) {
	s.mu.RLock()
	status = s.Aliveness
	s.mu.RUnlock()
	return
}

type ServerPool struct {
	currentPos uint64
	servers    []*Server
}

var pool ServerPool

func (p *ServerPool) Add(server *Server) {
	p.servers = append(p.servers, server)
}

func (p *ServerPool) NextPos() int {
	total := len(p.servers)
	return int(atomic.AddUint64(&p.currentPos /* addr */, uint64(1) /* val */) % uint64(total))
}

func (p *ServerPool) NextPeer() *Server {
	total := len(p.servers)
	nextPos := p.NextPos()
	cycle := total + nextPos
	for i := nextPos; i < cycle; i++ {
		pos := i % total // NOTE: Even if `i > total` --> Still `i % total == correctPos`.
		if p.servers[pos].IsAlive() {
			if i != nextPos {
				atomic.StoreUint64(&p.currentPos /* addr */, uint64(pos) /* val */)
			}
			return p.servers[pos]
		}
	}
	return nil
}

func (p *ServerPool) MarkStatus(hostURl *url.URL, aliveness bool) {
	for _, s := range p.servers {
		if s.URL.String() == hostURl.String() {
			s.SetAlive(aliveness)
			break
		}
	}
}

func (p *ServerPool) PingAll() {
	for _, s := range p.servers {
		status := "up"
		aliveness := isServerAlive(s.URL, 2 /* pingDuration */)
		s.SetAlive(aliveness)
		if !aliveness {
			status = "down"
		}
		log.Printf("%s [%s]\n", s.URL, status)
	}
}

func isServerAlive(hostURL *url.URL, pingDuration time.Duration) bool {
	timeout := pingDuration * time.Second
	conn, err := net.DialTimeout("tcp", hostURL.Host, timeout)
	if err != nil {
		log.Println("Site unreachable, error: ", err)
		return false
	}
	defer conn.Close()
	return true
}

const (
	Attempts = iota
	Retry
)

func countCtxBasedOnAction(req *http.Request, ctxLevel int) int {
	switch {
	case ctxLevel == Attempts:
		if attempts, ok := req.Context().Value(Attempts).(int); ok {
			return attempts
		}
		return 1

	case ctxLevel == Retry:
		if retries, ok := req.Context().Value(Retry).(int); ok {
			return retries
		}
		return 0

	default:
		return ctxLevel
	}
}

func healthCheckRoutine(duration time.Duration) {
	t := time.NewTicker(time.Minute * duration)
	for {
		select {
		case <-t.C:
			log.Println("Starting health-check process...")
			pool.PingAll()
			log.Println("Health-check process marks as completed!")

		}
	}
}

func lbHandler(w http.ResponseWriter, r *http.Request) {
	notAvailableMsg := "Server's current state is not available"
	maxAttempts := 3
	realAttempts := countCtxBasedOnAction(r, Attempts)
	if realAttempts > maxAttempts {
		log.Printf("%s(%s) Max attempts reached, terminating\n", r.RemoteAddr, r.URL.Path)
		http.Error(w /* ResponseWriter */, notAvailableMsg,
			http.StatusServiceUnavailable /* StatusCode */)
		return
	}

	var pool ServerPool
	peer := pool.NextPeer()
	if peer != nil {
		peer.ReverseProxy.ServeHTTP(w /* ResponseWriter */, r /* Request */)
	}
	http.Error(w /* ResponseWriter */, notAvailableMsg,
		http.StatusServiceUnavailable /* StatusCode */)
}

func splitServerArgs(args string, token string) ([]string, error) {
	if len(args) == 0 {
		return nil, errors.New("List of server arguments cannot be empty!")
	}
	if !strings.Contains(args, token /* comma */) {
		return nil, errors.New("List of server arguments must be comma-separated!")
	}
	return strings.Split(args, token), nil
}

func lbProxyServer(url *url.URL, maxRetries int /* 3 */, retryDuration time.Duration) *httputil.ReverseProxy {
	var newProxyServer *httputil.ReverseProxy

	newProxyServer = httputil.NewSingleHostReverseProxy(url)
	newProxyServer.ErrorHandler = func(w http.ResponseWriter, r *http.Request, err error) {
		log.Printf("[%s] %s\n", url.Host, err.Error())
		retries := countCtxBasedOnAction(r, Retry)
		if retries < maxRetries {
			select {
			case <-time.After(retryDuration * time.Microsecond /* 10ms */):
				ctx := context.WithValue(r.Context() /* ParentCtx */, Retry /* Key */, retries+1 /* Value */)
				newProxyServer.ServeHTTP(w /* ResponseWriter */, r.WithContext(ctx))
				return
			}
		}
		pool.MarkStatus(url, false) // NOTE: If number of retries is more than 3 times, marks the server as unavailable.

		attempts := countCtxBasedOnAction(r, Attempts)
		log.Printf("%s(%s) Attempting retry %d\n", r.RemoteAddr, r.URL.Path, attempts)
		ctx := context.WithValue(r.Context() /* ParentCtx */, Attempts /* Key */, attempts+1 /* Value */)
		lbHandler(w, r.WithContext(ctx))
	}

	return newProxyServer
}

func main() {
	var serverList string
	var port int
	flag.StringVar(&serverList, "servers", "", "Usage: Load balanced servers, use commas to separate")
	flag.IntVar(&port, "port", 9999, "Usage: Port to serve")
	flag.Parse()

	if len(serverList) == 0 {
		log.Println("Please provide one or more backends to load balance!")
	}

	servers, _ := splitServerArgs(serverList, ",")
	for _, s := range servers {
		url, err := url.Parse(s)
		if err != nil {
			log.Println("Error parsing URL: ", err)
		}

		proxy := lbProxyServer(url, 3 /* maxRetries */, 10 /* retryDuration */)
		pool.Add(&Server{
			URL:          url,
			Aliveness:    true,
			ReverseProxy: proxy,
		})
		log.Printf("Configured server: %s\n", url)
	}

	newServer := http.Server{
		Addr:    fmt.Sprintf(":%d", port),
		Handler: http.HandlerFunc(lbHandler),
	}

	go healthCheckRoutine(1 / 2 /* Half of a minute */)
	log.Printf("Load Balancer started at :%d\n", port)
	if err := newServer.ListenAndServe(); err != nil {
		log.Fatal(err)
	}
}
