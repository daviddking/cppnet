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
using namespace std::placeholders;

int const DAYTIME_PORT = 8013;

static void glob_write_handler(const std::error_code& error, std::size_t bytes_transferred) {

}


class daytime_tcp_connection {
public:
    daytime_tcp_connection(tcp::socket&& client_socket)  : client_socket{std::move(client_socket)}
    {
    }

    void write_handler(error_code& error, size_t bytes_transferred) {

    }

    void start() {
        string message = current_date_and_time();
        client_socket.async_write_some(
                buffer(message),
                &glob_write_handler);
//                bind(&daytime_tcp_connection::write_handler, this, _1, _2));
    }


private:
    tcp::socket client_socket;
};


class daytime_tcp_server {
public:
    daytime_tcp_server(shared_ptr<io_context> io, unsigned short listen_port) :
            io{io}, acceptor{*io, tcp::endpoint{tcp::v4(), listen_port}}
    {}

    void start_accept() {
        acceptor.async_accept(bind(&daytime_tcp_server::accept_handler, this, _1, _2));
    }

    void accept_handler(const error_code& error, tcp::socket client_socket) {
        if (!error) {
            auto client_connection =
                    make_shared<daytime_tcp_connection>(client_socket);
            client_connection->start();
        }
        start_accept();
    }

private:
    shared_ptr<io_context> io;
    tcp::acceptor acceptor;
};

int main() {
    auto io = make_shared<io_context>();
    daytime_tcp_server tcpServer{io, DAYTIME_PORT};
    io->run();
}

#pragma clang diagnostic pop