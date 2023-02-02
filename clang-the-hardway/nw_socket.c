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
  *   Datagram Sockets are somtimes called "connectionless sockets" (unreliable) ("Raw Sockets" is also powerful).
  *
  * - Stream Sockets: are reliable 2-way connected communication streams, preserve the order of data transmission, error-free.
  *   `telnet` or `ssh` applications are using stream sockets.
  * - "The Transmission Control Protocol (TCP)": make sure our data arrives squentially and eror-free.
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
  *           -> this acknownledgement procedure is very important when implementing reliable `SOCK_DGRAM` applications.
  *   Speed: it's way faster to fire-and-forget than to keep track of what has arrived safely and make sure it's in order and that all.
  *
  * - Preference domain for each protocol:
  *   + TCP: Chat messages, etc.
  *   + UDP: Sending 40 positional update per second of the players (game domain), etc.
  */