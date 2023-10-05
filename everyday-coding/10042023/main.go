package main

import (
	"fmt"
	"log"
	"net"
	"net/http"
	"strconv"

	"golang.org/x/exp/slices"
	"golang.org/x/sync/singleflight"
)

func collectLocalNwAddrs() []string {
	ifaces, _ := net.Interfaces()
	addrs := make([]string, 0, len(ifaces))
	netAddrsToSliceFnOnce := func(addrs []net.Addr) []string {
		convertedAddrs := make([]string, 0, len(addrs))
		for _, addr := range addrs {
			convertedAddrs = append(convertedAddrs, addr.String())
		}
		return convertedAddrs
	}
	for _, i := range ifaces {
		errorFreeAddrs, _ := i.Addrs()
		addrs = append(netAddrsToSliceFnOnce(errorFreeAddrs), addrs...)
	}
	return slices.Compact(addrs)
}

func main() {
	var sfg = singleflight.Group{}

	allAbtIPs := collectLocalNwAddrs()
	for _, addr := range allAbtIPs {
		log.Println(addr)
	}
	http.HandleFunc("/addresses", func(w http.ResponseWriter, r *http.Request) {
		queriedAddr := r.URL.Query().Get("ip_pos")
		// NOTE: Singleflight implementation.
		resp, _, _ := sfg.Do(queriedAddr, func() (interface{}, error) {
			if curPos, err := strconv.Atoi(queriedAddr); err != nil ||
				(curPos >= len(allAbtIPs) || curPos < 0) {
				return "You sucks, dude!", nil
			} else {
				log.Printf("Howdy, looks how far you have become!!!")
				return allAbtIPs[curPos], nil
			}
		})
		fmt.Fprint(w, resp, "\n")
	})
	// Exp: `curl "http://localhost:8888/addresses?ip_pos=3"`.
	err := http.ListenAndServe(":8888", nil)
	if err != nil {
		log.Println(err)
	}
}
