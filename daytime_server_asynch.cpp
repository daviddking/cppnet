#include <iostream>
#include <experimental/net>
#include "daytime.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::net;
using namespace std::experimental::net::ip;
using namespace std::placeholders;

int const DAYTIME_PORT = 8013;

class daytime_tcp_connection {
public:
    daytime_tcp_connection(tcp::socket&& client_socket)  :
            client_socket{std::move(client_socket)},
            result{}, total_bytes_written{0}
    {
    }

    void start() {
        result = current_date_and_time();
        client_socket.async_write_some(
                buffer(result),
                std::bind(&daytime_tcp_connection::write_handler, this, _1, _2));
    }

    void write_handler(const error_code& error, size_t bytes_transferred) {
        // Handle possibility of a partial write
        total_bytes_written += bytes_transferred;
        if (total_bytes_written < result.length()) {
            // Does the API support better handling of partial writes?
            // Perhaps a more stateful buffer class would help?
            client_socket.async_write_some(
                    buffer(result.substr(total_bytes_written)),
                    std::bind(&daytime_tcp_connection::write_handler, this, _1, _2));
        }
    }

private:
    tcp::socket client_socket;
    string result;
    size_t total_bytes_written;
};


class daytime_tcp_server {
public:
    daytime_tcp_server(shared_ptr<io_context> io, unsigned short listen_port) :
            io{io}, acceptor{*io, tcp::endpoint{tcp::v4(), listen_port}}
    {
        cout << "Listening on TCP port " << listen_port << "..." << endl;
        start_accept();
    }

    void start_accept() {
        acceptor.async_accept(std::bind(&daytime_tcp_server::accept_handler, this, _1, _2));
    }

    void accept_handler(const error_code& error, tcp::socket client_socket) {
        if (!error) {
            auto client_connection = make_shared<daytime_tcp_connection>(std::move(client_socket));
            client_connection->start();
        }
        start_accept();
    }

private:
    shared_ptr<io_context> io;
    tcp::acceptor acceptor;
};

class daytime_udp_server {
public:
    daytime_udp_server(shared_ptr<io_context> io, unsigned short listen_port) :
            io{io}, socket{*io, udp::endpoint{udp::v4(), listen_port}}
    {
        cout << "Listening on UDP port " << listen_port << "..." << endl;
        start_receive();
    }

    void start_receive() {
       socket.async_receive_from(
            buffer(receive_buffer),
            remote_endpoint,
            std::bind(&daytime_udp_server::receive_handler, this, _1, _2)
       );
    }

    void receive_handler(const error_code& error, size_t bytes_transferred) {
        if (!error) {
            auto message = make_shared<string>(current_date_and_time());
            socket.async_send_to(
                    buffer(*message),
                    remote_endpoint,
                    std::bind(&daytime_udp_server::send_handler, this, message, _1, _2)
            );
        }
    }

    void send_handler(shared_ptr<string> message,
                         const error_code& error, size_t bytes_transferred) {
        // No good way to handle partial writes in this implementation.
        // It's not clear from the API documentation whether the initial call
        // to async_send_to will necessarily transfer all bytes.
    }

private:
    shared_ptr<io_context> io;
    udp::socket socket;
    udp::endpoint remote_endpoint;
    std::array<char,1024> receive_buffer;
};

int main() {
    auto io = make_shared<io_context>();
    daytime_tcp_server tcpServer{io, DAYTIME_PORT};
    daytime_udp_server udpServer{io, DAYTIME_PORT};
    io->run();
}

#pragma clang diagnostic pop