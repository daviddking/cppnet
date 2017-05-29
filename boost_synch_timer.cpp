#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

int main() {
    io_service io;
    deadline_timer timer{io, seconds(3)};
    timer.wait();
    cout << "Timer fired!" << endl;
    return 0;
}