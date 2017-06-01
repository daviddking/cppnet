#include <iostream>
#include <algorithm>
#include <experimental/net>
#include "http_pages.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::net;
using namespace std::experimental::net::ip;
using namespace std::placeholders;

int const HTTP_PORT = 8080;
int const MAX_REQUEST_SIZE = 1024;

class http_server;
class http_connection;

class http_connection {
public:
    http_connection(http_server* server, tcp::socket&& client_socket)  :
            server{server},
            client_socket{std::move(client_socket)},
            request_buffer{},
            request_length_read{0},
            response_length_written{0}
    {}

    void start() {
        client_socket.async_read_some(
                buffer(request_buffer, MAX_REQUEST_SIZE),
                std::bind(&http_connection::read_handler, this, _1, _2)
        );
    }

    void read_handler(const error_code& error, size_t bytes_transferred) {
        if (!error) {
            request_length_read += bytes_transferred;
            if (has_full_request()) {
                request_handler();
            }
            else {
                client_socket.async_read_some(
                        buffer(request_buffer, MAX_REQUEST_SIZE),
                        std::bind(&http_connection::read_handler, this, _1, _2)
                );
            }
        }
    }

    void request_handler() {
        string request_string{begin(request_buffer), begin(request_buffer) + request_length_read};

        // get first line
        istringstream iss{request_string};
        string line;
        getline(iss, line);

        // parse it
        istringstream isl{line};
        vector<string> tokens{istream_iterator<string>{isl}, istream_iterator<string>{}};
        string http_verb = tokens[0];
        string path = tokens[1];
        string http_version = tokens[2];

        if (http_verb == "GET") {
            http_get_request_handler(path);
        }
        else {
            close();
        }
    }

    void http_get_request_handler(const string &path) {
        response_buffer +=
                "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=ISO-8859-1\r\nConnection: close\r\n\r\n";
        response_buffer += get_page(path);

        client_socket.async_write_some(
                buffer(response_buffer),
                std::bind(&http_connection::write_handler, this, _1, _2)
        );
    }

    void write_handler(const error_code& error, size_t bytes_transferred) {
        if (!error) {
            response_length_written += bytes_transferred;
            if (response_length_written < response_buffer.length()) {
                client_socket.async_write_some(
                        buffer(response_buffer.substr(response_length_written)),
                        std::bind(&http_connection::write_handler, this, _1, _2)
                );
            }
            else {
                close();
            }
        }
    }

    bool has_full_request() const {
        // For this toy server, we're happy if we just have the
        // initial request line
        auto last = begin(request_buffer) + request_length_read;
        return (std::find(begin(request_buffer), last, '\n') != last);
    }

    void close();

private:
    http_server* server;
    tcp::socket client_socket;
    std::array<char,MAX_REQUEST_SIZE> request_buffer;
    string response_buffer;
    size_t request_length_read;
    size_t response_length_written;
};


class http_server {
public:
    http_server(shared_ptr<io_context> io, unsigned short listen_port) :
            io{io}, acceptor{*io, tcp::endpoint{tcp::v4(), listen_port}},
            connections{}
    {
        cout << "Listening on TCP port " << listen_port << "..." << endl;
        start_accept();
    }

    void start_accept() {
        acceptor.async_accept(std::bind(&http_server::accept_handler, this, _1, _2));
    }

    void accept_handler(const error_code& error, tcp::socket client_socket) {
        if (!error) {
            auto client_connection = make_shared<http_connection>(this, std::move(client_socket));
            connections.push_back(client_connection);
            client_connection->start();
        }
        start_accept();
    }

    void close(const http_connection* connection) {
        connections.erase(
                std::remove_if(
                        connections.begin(),
                        connections.end(),
                        [connection](auto& conn_ptr) { return (conn_ptr.get() == connection); }),
                connections.end()
        );
    }

private:
    shared_ptr<io_context> io;
    tcp::acceptor acceptor;
    std::vector<shared_ptr<http_connection>> connections;
};

void http_connection::close() {
    server->close(this);
}

int main() {
    auto io = make_shared<io_context>();
    http_server tcpServer{io, HTTP_PORT};
    io->run();
}

#pragma clang diagnostic pop