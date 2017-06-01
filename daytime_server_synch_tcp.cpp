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

int const HTTP_PORT = 8013;


int main() {
    io_context io;
    tcp::acceptor acceptor{io, tcp::endpoint{tcp::v4(), HTTP_PORT}};
    cout << "Listening on TCP port " << HTTP_PORT << " ..." << endl;
    for ( ;; ) {
        auto socket = acceptor.accept();
        socket.send(buffer(current_date_and_time()));
    }
}
#pragma clang diagnostic pop