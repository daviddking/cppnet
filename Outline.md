# C++ Networking

* We are going to write tools in C++ to explore the TCP/IP networking
  stack. Along the way we'll learn (or refresh) our knowledge of
  networking and learn how to wield the C++ networking APIs.

* History - packet switching, ARPANET

* Routing problem

* IP
    * Physical network, Layering
        * MAC addresses, ARP, UUIDs
        * network interfaces
        * ifconfig
    * Addressing
        * v4, v6
    * Routing
        * Packet loss, best-effort delivery
        * TTL
        * MTU, Fragmentation
        * ICMP
    * (Brief Intro to C++ networking APIs)
    * ping
    * traceroute
    * wireshark
* UDP
    * ports
    * (Better intro to networking TS)
    * time server
    * NNTP, time synch server 
* DNS
    * nslookup
* TCP
    * telnet
    * nmap
    * (Client server programming models, asynch I/O)
    * http server
* (Other networking API details?)
* TLS
* Multicast
    * reliable multicast

* Notes
    * Asynchronous and synchronous operations side-by-side
    * What's going on in io.run()?
    * Co-routines? See Kohlhoff's BoostCon11 presentation
