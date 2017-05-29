#include <iostream>
#include <chrono>
#include <experimental/io_context>
#include <experimental/timer>

using namespace std;
using namespace std::experimental::net;
using namespace std::literals::chrono_literals;
using namespace std::placeholders;
using namespace std::chrono;


class printer {
public:
    printer(shared_ptr<io_context> io, duration period) :
            io{io}, count{0}, period{period}, timer{*io, period} {
        timer.async_wait(bind(&printer::print, this));
    }

    void print() {
        count++;
        cout << "Timer fired, count: " << count << endl;
        timer.expires_after(period);
    }

private:
    shared_ptr<io_context> io;
    int count;
    duration period;
    system_timer timer;
};

int main() {
    shared_ptr<io_context> io = make_shared(1s);
    printer p{io, 1s};
    io->run();
    return 0;
}