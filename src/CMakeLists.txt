cmake_minimum_required(VERSION 3.7)
project(cppnet)

set(CMAKE_CXX_STANDARD 14)
set(BOOST_ROOT /home/david/opt/boost_1_64_0)

include_directories(${BOOST_ROOT})
add_executable(ping ping.cpp)
add_executable(timer_synchronous_boost timer_synchronous_boost.cpp)