#include <iostream>
#include <chrono>
#include <experimental/net>


using namespace std;
using namespace std::experimental::net;
using namespace std::literals::chrono_literals;

int main() {
    io_context io;
    system_timer timer{io, 3s};
    timer.wait();
    cout << "Timer fired!" << endl;
    return 0;
}