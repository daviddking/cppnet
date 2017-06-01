#include <iostream>
#include <experimental/net>
#include "daytime.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::net;
using namespace std::experimental::net::ip;

int const HTTP_PORT = 8013;

int main() {
    io_context io;
    udp::socket socket{io, udp::endpoint{udp::v4(), HTTP_PORT}};
    cout << "Listening on UDP port " << HTTP_PORT << "..." << endl;
    std::array<char, 1024> receive_buffer;
    for ( ;; ) {
        udp::endpoint remote_endpoint;
        socket.receive_from(buffer(receive_buffer), remote_endpoint);
        socket.send_to(buffer(current_date_and_time()), remote_endpoint);
    }
}
#pragma clang diagnostic pop

