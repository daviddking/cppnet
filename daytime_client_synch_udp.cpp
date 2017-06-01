#include <iostream>
#include <experimental/net>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::net;
using namespace std::experimental::net::ip;


int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "usage: daytime_client <server> <port>" << endl;
        cout << argc << endl;
    }
    io_context io;

    // DNS query for IP endpoint
    udp::resolver resolver{io};
    auto results = resolver.resolve(udp::v4(), argv[1], argv[2]);

    // Choose the first endpoint
    udp::endpoint remote_endpoint = results.begin()->endpoint();

    // Open the socket (can send to multiple endpoints)
    udp::socket socket{io};
    socket.open(udp::v4());

    std::array<char,1> send_buffer = {{0}};
    socket.send_to(buffer(send_buffer), remote_endpoint);

    std::array<char,1024> receive_buffer;
    udp::endpoint local_endpoint;
    // Does the API support timeouts on blocking operations?
    size_t length = socket.receive_from(buffer(receive_buffer), local_endpoint);

    cout.write(receive_buffer.data(), length);

}
