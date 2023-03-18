package main

import (
	"net/http"
	"net/http/httputil"
	"net/url"
	"sync"
	"sync/atomic"
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

func (p *ServerPool) NextPos() int {
	total := len(p.servers)
	return int(atomic.AddUint64(&p.currentPos /* addr */, uint64(1) /* val */) % uint64(total))
}

func (p *ServerPool) GetNextPeer() *Server {
	total := len(p.servers)
	nextPos := p.NextPos()
	cycle := total + nextPos
	for i := nextPos; i < cycle; i++ {
		pos := i % total // NOTE: `i > total` --> `i % total == correctPos`.
		if p.servers[pos].IsAlive() {
			if i != nextPos {
				atomic.StoreUint64(&p.currentPos /* addr */, uint64(pos) /* val */)
			}
			return p.servers[pos]
		}
	}
	return nil
}

func lbHandler(w http.ResponseWriter, r *http.Request) {
	var pool ServerPool
	peer := pool.GetNextPeer()
	if peer != nil {
		peer.ReverseProxy.ServeHTTP(w /* ResponseWriter */, r /* Request */)
	}
	http.Error(w /* ResponseWriter */, "Server's current state is not available",
		http.StatusServiceUnavailable /* code */)
}
