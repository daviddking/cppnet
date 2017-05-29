#include <iostream>
#include <chrono>
#include <experimental/io_context>
#include <experimental/timer>

using namespace std;
using namespace std::experimental::net;
using namespace std::literals::chrono_literals;
using namespace std::placeholders;

void printer(const std::error_code &status, system_timer &timer, int &count) {
    count++;
    cout << "Timer fired, count: " << count << endl;
    timer.expires_after(1s);
    timer.async_wait(std::bind(printer, _1, std::ref(timer), count));
}

int main() {
    int count = 0;
    io_context io;
    system_timer timer{io, 1s};
    timer.async_wait(std::bind(printer, _1, std::ref(timer), count));
    io.run();
    return 0;
}