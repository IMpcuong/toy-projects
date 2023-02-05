/**
 *
 * NOTE:
 * - Learn basic C syntax from this source: https://www.cbyexample.com/#type-qualifiers.
 * - Learn Socket for beginners from this source: https://beej.us/guide/bgnet/html/#what-is-a-socket.
 *
 * - Socket definition: a way to speak to other programs using standard Unix file descriptors.
 * - Unix programs do any sort of I/O, they do it by reading or writing a file descriptor.
 * - A file descriptor is simply an integer associated with an open file. That file can be a network connection,
 *   a FIFO, a pipe, a terminal, a real on-the-disk file, or anything else that you could imagine.
 *
 * - All kind of sockets can be listed adjacently: DARPA Internet addresses (Internet Sockets), path names on a local nodes
 *   (Unix Sockets), CCITT X.25 addresses (X.25 Sockets ignorable), etc. This document mainly focus on the first: Internet Sockets.
 * - We're only dealing with 2 types of Internet Sockets here: "Stream Sockets" (`SOCK_STREAM`) and "Datagram Sockets" (`SOCK_DGRAM`),
 *   Datagram Sockets are sometimes called "connectionless sockets" (unreliable) ("Raw Sockets" is also powerful).
 *
 * - Stream Sockets: are reliable 2-way connected communication streams, preserve the order of data transmission, error-free.
 *   `telnet` or `ssh` applications are using stream sockets.
 * - "The Transmission Control Protocol (TCP)": make sure our data arrives sequentially and error-free.
 *   "TCP/IP": where "IP" stands for "Internet Protocol", deals primarily with Internet routing and not generally responsible for data integrity.
 *
 * - Facts: if you send a datagram (datagram := {data[1..n]})
 *           -> may arrive or not
 *           -> may arrive out of order
 *           -> if it arrives, the data within the packet will be error-free.
 * - Datagram Sockets: also use for IP routing, but they don't use TCP; they use the "User Datagram Protocol", or "UDP".
 *   Connectionless: you don't have to maintain an open connection as you do with stream sockets.
 *   Procedure: build a packet
 *               -> slap an IP header on it with destination information
 *               -> send it out.
 *   No connection needed, they are generally used either TCP stack are unavailable or when a few dropped packets are acceptable.
 *   `tftp` (trivial file transfer protocol), `dhpcd` (a DHCP client), multiplayer games, streaming audio, video conferencing, etc.
 *   Facts: Data can be lost when it arrives, but the application still work as expected
 *           -> `tftp` and similar programs have their own protocol on top of UDP
 *           -> the `tftp` protocol says that for each packet that gets sent,
 *              the recipient has to send back a packet that says, "I got it!" (an "ACK" packet)
 *           -> if the sender of the original packet gets no reply in (e.g. 5 secs),
 *              he'll re-transmit the packet until he finally gets an ACK.
 *           -> this acknowledgement procedure is very important when implementing reliable `SOCK_DGRAM` applications.
 *   Speed: it's way faster to fire-and-forget than to keep track of what has arrived safely and make sure it's in order and that all.
 *
 * - Preference domain for each protocol:
 *   + TCP: Chat messages, etc.
 *   + UDP: Sending 40 positional update per second of the players (game domain), etc.
 *
 * - Data Encapsulation (flow chart):
 *   Packet born -> packet wrapped ("encapsulated") in a header (rarely footer) in the first protocol (e.g. TFTP protocol)
 *               -> then the whole thing (TFTP header included) is encapsulated again by the next protocol (e.g. UDP)
 *               -> then again by the next (IP)
 *               -> finalize by the hardware-based (physical-based) protocol (e.g. Ethernet).
 *   Packet receive -> hardware strips the Ethernet header
 *                  -> the kernel strips the IP and UDP headers
 *                  -> the TFTP strips the TFTP header
 *                  -> finally has the data for user.
 *
 * - Layer Network Model (aka OSI/ISO): this model describes a system of network functionally that has many advantages over other models.
 *   For instance, you can write sockets programs that are exactly the same without caring how the data physically transmitted
 *   (serial, thin Ethernet, AUI, etc) because program on the low-levels will deal with it for you. The actual network hardware and topology is transparent
 *   to the socket programmers.
 *   7 Layers of the full-blown model:
 *     + Application (users interact with the network)
 *     + Presentation
 *     + Session
 *     + Transport
 *     + Network
 *     + Data Link
 *     + Physical (serial, Ethernet, etc)
 *   A layered model more consistent with Unix might be:
 *     + Application Layer (telnet, ftp, etc)
 *     + Host-to-Host Transport Layer (TCP, UDP)
 *     + Internet Layer (IP and routing)
 *     + Network Access Layer (Ethernet, wi-fi, etc)
 *   The kernel builds the Transport Layer and the Internet Layer on for us, and the hardware does the Network Access Layer.
 *   The routers strips the packet to the IP header, consults its routing table (https://www.rfc-editor.org/rfc/rfc791).
 *
 * - IP addresses and ports sorted out, how the sockets API stores and manipulates IP addresses and other data:
 *   + Network routing system "The Internet Protocol Version 4 ~ IPv4": where addresses made up for 4 bytes ~ 4 octets (8 bits * 4 octets := 32 bits),
 *     commonly written in "dots and numbers" form: `192.0.12.111`. Total amount of addresses IPv4 system can be provided ~ 2^32 abilities.
 *   + "The Internet Protocol Version 6 ~ IPv6": 2^128 addresses in the hexadecimal representation, with each 2-byte chunk separated by a colon. E.g.:
 *     `2001:0db8:c9d2:aee5:73e3:934a:a5ae:9551`
 *
 *     `2001:0db8:c9d2:0012:0000:0000:0000:0051`
 *     `2001:db8:c9d2:12::51`
 *
 *     `2001:0db8:ab00:0000:0000:0000:0000:0000`
 *     `2001:db8:ab00::`
 *
 *     `0000:0000:0000:0000:0000:0000:0000:0001`
 *     `::1` is the loopback address. It always means “this machine I’m running on now”. In IPv4, the loopback address is `127.0.0.1`.
 *   + Conversion between IPv4/IPv6: `192.0.2.33` <-> `::ffff:192.0.2.33`.
 */