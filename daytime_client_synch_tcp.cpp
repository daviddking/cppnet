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
    tcp::resolver resolver{io};
    auto results = resolver.resolve(argv[1], argv[2]);
    for (auto result : results) {
        cout << result.endpoint() << endl;
    }

    // Connect to server
    tcp::socket socket{io};
    connect(socket, results);

    // Read the response
    array<char, 1024> receive_buffer;

    for ( ;; ) {
        error_code erc;
        size_t length = socket.read_some(buffer(receive_buffer), erc);

        if (erc == error::eof) {
            // Connection closed by server
            break;
        }
        else if (erc) {
            throw system_error{erc};
        }

        cout.write(receive_buffer.data(), length);
    }
}
