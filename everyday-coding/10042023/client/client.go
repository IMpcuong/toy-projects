package main

import (
	"io"
	"log"
	"net/http"
	"strconv"
	"sync"
)

const (
	ENDPOINT   string = "http://localhost:8888/addresses?ip_pos="
	TOTAL_REQS int    = 12
)

func triggerAPIFrom(endpoint string) {
	resp, _ := http.Get(endpoint)
	body, _ := io.ReadAll(resp.Body)
	log.Print(string(body))
}

func main() {
	var wg sync.WaitGroup
	for i := 0; i < TOTAL_REQS; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			triggerAPIFrom(ENDPOINT + strconv.Itoa(i))
		}(i)
	}
	wg.Wait()
}
