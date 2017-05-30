#include <iostream>
#include <chrono>
#include <experimental/io_context>
#include <experimental/timer>

using namespace std;
using namespace std::experimental::net;
using namespace std::literals::chrono_literals;

int main() {
    io_context io;
    system_timer timer{io, 3s};
    timer.async_wait([](const error_code &status) {
        cout << "Timer fired!" << endl;
    });
    io.run();
    return 0;
}