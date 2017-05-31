#ifndef CPPNET_DAYTIME_H
#define CPPNET_DAYTIME_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

std::string current_date_and_time()  {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X\n");
    return ss.str();
}


#endif //CPPNET_DAYTIME_H
