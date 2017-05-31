#include "clion_syntax_highlight.h"
#include <iostream>
#include <experimental/net>
#include "daytime.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::net;
using namespace std::experimental::net::ip;

int const DAYTIME_PORT = 8013;

class daytime_tcp_server {
public:
    daytime_tcp_server(shared_ptr<io_context> io, int listen_port) :
            io{io}, acceptor{tcp::v4(), listen_port}
    {}

    void start_accept() {
        
    }

private:
    shared_ptr<io_context> io;
    tcp::acceptor acceptor;
};

int main() {
    io_context io;
    tcp_server tcpServer{io, DAYTIME_PORT};
    io.run();
}
#pragma clang diagnostic pop