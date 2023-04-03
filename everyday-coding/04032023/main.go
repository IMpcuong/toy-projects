package main

import (
	"fmt"
	"net"

	"github.com/google/gopacket"
	"github.com/google/gopacket/pcap"
)

const (
	TH32CS_SNAPPROCESS = 0x00000002
	MAX_PATH           = 260
	DEFAULT_SNAPLEN    = 262144
)

func snapshotLivePackets(iface string, portExpr string) (<-chan gopacket.Packet, error) {
	handler, err := pcap.OpenLive(iface, DEFAULT_SNAPLEN, true, pcap.BlockForever)
	defer handler.Close()
	if err != nil {
		panic(err)
	}
	if err := handler.SetBPFFilter(portExpr); err != nil {
		panic(err)
	}
	packetSrc := gopacket.NewPacketSource(handler, handler.LinkType())
	packets := packetSrc.Packets()
	return packets, nil
}

func detectNetInterfaces() ([]net.Interface, error) {
	interfaces, err := net.Interfaces()
	if err != nil {
		return nil, err
	}
	return interfaces, nil
}

func detectListAddrsFrom(iface net.Interface, networkType string) ([]*net.IPAddr, error) {
	ipAddrs := make([]*net.IPAddr, 0)
	addrs, err := iface.Addrs()
	if err != nil {
		return nil, err
	}
	for _, addr := range addrs {
		ipNet, ok := addr.(*net.IPNet)
		if !ok {
			continue
		}
		if ipNet.IP.To4() == nil {
			continue
		}
		ipAddrs = append(ipAddrs, &net.IPAddr{IP: ipNet.IP, Zone: ipNet.Network()})

		listener, err := net.ListenTCP(networkType, &net.TCPAddr{IP: ipNet.IP})
		if err != nil {
			continue
		}
		defer listener.Close()
		fmt.Printf("Listening on port %d...\n", listener.Addr().(*net.TCPAddr).Port)
	}
	return ipAddrs, nil
}

func main() {
	var interfaces []net.Interface
	interfaces, _ = detectNetInterfaces()
	for _, iface := range interfaces {
		fmt.Println("[INFO]: Network interface >> ", iface.Name)
		ipAddrs, _ := detectListAddrsFrom(iface, "tcp4")
		for _, addr := range ipAddrs {
			fmt.Printf("%+v\n", *addr)
		}
		packets, _ := snapshotLivePackets(iface.Name, "port 9999")
		for pkt := range packets {
			fmt.Printf("%#v\n", pkt.Data())
		}
	}
}
