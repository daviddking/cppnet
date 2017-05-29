cmake_minimum_required(VERSION 3.7)
project(cppnet)

set(CMAKE_CXX_STANDARD 14)

# Requires boost
# To install boost on Ubuntu:
#     sudo apt-get install libboost-all-dev
find_package(Boost REQUIRED COMPONENTS date_time filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(boost_synch_timer boost_synch_timer.cpp)
target_link_libraries(boost_synch_timer ${Boost_LIBRARIES})
