# C++ Networking

* History
    * Packet switching early 60's
    * 1974 - Cerf/Kahn TCP/IP paper
    * 1983 - TCP/IP deployed on the ARPANET
    
* Routing
    * Adapt disparate physical networks
    * Decentralized 
    * Draw routing diagram, tables, next hop
    
* Encapsulation
    * Draw sample encapsulated packet
    * Stack:
        * (7)   Application:     HTTP, DNS, etc.)
        * (4.5) Security:        TLS
        * (4)   Transport:       TCP, UDP, SCTP
        * (3.5) Network (adj) :  ICMP, IGMP
        * (3)   Network :        IP
        * (2)   Link/Physical:   Ethernet, 802.11
    * OSI:
        * (7) Application
        * (6) Presentation
        * (5) Session
        * (4) Transport
        * (3) Network
        * (2) Link
        * (1) Physical
        
* Won't talk about physical layer (deeply abstracted)
    * Could use carrier pigeons
    
* IP tenets:
    * "Smarts" built-in to endpoints. Network is "dumb".
        * Once-and-only once (reliability, deduplication)
        * In-order delivery
        * Flow control
        * Congestion control
        * Security
    * IP layer handles only:
        * Routing (shortest path)
        * Best-effort delivery (why can packets be dropped?)
        * Cycle prevention
        * Minimal error correction

* IP packet
    * Source address
    * Destination address
    * Protocol
    * TTL 
    * Fragmentation info
    * Header checksum
    * Length
    * Note:
        * 127.0.0.1 loopback
        * 224.0.0.0 - 239.255.255.255 (mcast)
        * 10.x.x.x, 192.168.x.x (private) NAT
        
* UDP
    * Source port
    * Destination port
    * Total Checksum
    * Provides:
        * Application (process) dispatch
        * Error detection
    * Port numbers - what is port?
        * < 1024, > 32k Ephemeral ports
        * 22 SSH, 80 HTTP, 443 HTTPS, ...

* TCP
    * Connected reliable full-duplex stream abstraction
    * Once-and-only-once, in-order delivery
    * Flow control, congestion control
    * Error detection
    * Header:
        * Source port
        * Destination port
        * Total Checksum
        * Sequence number
        * Ack number
        * Window size
        * Type
    * Sequence number established during 3-way handshake
        * SYN, SYN/ACK, ACK
    * 4-way shutdown
        * FIN+ACK,ACK,FIN+ACK,ACK
    * Sliding window with timeout
    * Turn off Nagle's algorithm!

* DNS
    * Resolve

* TLS
    * Transport layer security
    * Browser has CA root certificates installed, establish chain of trust

* Multicast
    * IGMP join group
        

* APIs:
    * System call interface (BSD sockets)
        * socket(protocol) -> fd
        * bind(fd,endpoint/port)
        * connect(fd,remote)
        * listen(fd,backlog)
        * accept(fd)->(newfd,remote)
        * send(fd,buf,len)
        * recv(fd,buf,len)
        * sendto(fd,buf,len,remote)
        * recvfrom(fd,buf,len,remote)
        * close(fd)
        * shutdown(fd,side)
    * endpoint/remote = (ip,port,protocol)
    * udp/tcp listen on same port
    * async IO
        * epoll_create()->efd
        * epoll_ctl(efd, op, fd)
        * epoll_wait(epfd, timeout)

* C++
    * Net TS subset of Boost ASIO
    * Includes:
        * TCP,UDP sockets
        * DNS resolve
        * Timers
    * Does not include:
        * Raw sockets (ICMP)
        * Signals
    * Integration with std:
        * Chrono
        * Async
        * C++11 move, etc.
        * API cleanup
    * Async IO: kqueue, epoll, win overlapped IO
    * Buffer types (will see)
    * Enough - Look at code
    * Compare models 
       * Iterative
       * Thread-per-request
       * Thread-pool
       * Async
    * Proactor versus reactor (completion handlers)
        * Caller initiates async ops (same)
        * Async Op Processor (e.g. epoll)
        * Event handler are placed on completion event handler queue
          (coupled with events)
        * Async Event Demultiplexer waits on handler queue 
          and dispatchers to handler
    * Notes:
        * Note composition in async mode
        * Beware managing socket lifetime
        * TCP partial reads annoying
        * Buffer state annoying   
        * Buffer space needs to be allocated up-front versus reactor                                                                        

* How would you implement?
    * Web crawler
    * Chat server
    * Nmap
    * Traceroute

* Tools:
    * ifconfig
    * nslookup (dig)
    * ping
    * traceroute
    * netstat
    * telnet
    * sock
    * wireshark, tcpdump
    * nmap
 
* Will e-mail links + references to Mike to forward.

         
        
                

