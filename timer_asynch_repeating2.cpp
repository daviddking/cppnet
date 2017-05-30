#include <iostream>
#include <chrono>
#include <experimental/net>


using namespace std;
using namespace std::experimental::net;
using namespace std::literals::chrono_literals;
using namespace std::placeholders;
using namespace std::chrono;


class printer {
public:
    printer(shared_ptr<io_context> io, system_timer::duration period) :
            io{io}, count{0}, period{period}, timer{*io, period} {
        timer.async_wait(bind(&printer::print, this));
    }

    void print() {
        count++;
        cout << "Timer fired, count: " << count << endl;
        timer.expires_after(period);
        timer.async_wait(bind(&printer::print, this));
    }

private:
    shared_ptr<io_context> io;
    int count;
    system_timer::duration period;
    system_timer timer;
};

int main() {
    auto io = make_shared<io_context>();
    printer p{io, 1s};
    io->run();
    return 0;
}