package main

import (
	"fmt"
	"net"
	"net/http"
	"strconv"
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
	return addrs
}

func main() {
	allAbtIPs := collectLocalNwAddrs()
	for _, addr := range allAbtIPs {
		fmt.Println(addr)
	}
	http.HandleFunc("/addresses", func(w http.ResponseWriter, r *http.Request) {
		queriedAddr := r.URL.Query().Get("ip_pos")
		if curPos, err := strconv.Atoi(queriedAddr); curPos >= len(allAbtIPs) || curPos < 0 || err != nil {
			fmt.Fprint(w, "You sucks, dude!")
		} else {
			fmt.Fprint(w, allAbtIPs[curPos], "\n")
		}
	})
	// Exp: `curl "http://localhost:8888/addresses?ip_pos=3"`.
	err := http.ListenAndServe(":8888", nil)
	if err != nil {
		fmt.Println(err)
	}
}
