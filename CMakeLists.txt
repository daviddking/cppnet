cmake_minimum_required(VERSION 3.7)
project(cppnet)

set(CMAKE_CXX_STANDARD 14)
set(NETWORKING_TS_ROOT "/home/david/git/networking-ts-impl")

# Requires boost
# To install boost on Ubuntu:
#     sudo apt-get install libboost-all-dev
find_package(Boost REQUIRED COMPONENTS date_time filesystem system)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${NETWORKING_TS_ROOT}/include)

add_executable(boost_synch_timer boost_synch_timer.cpp)
target_link_libraries(boost_synch_timer ${Boost_LIBRARIES})

add_executable(netts_synch_timer netts_synch_timer.cpp)
target_link_libraries(netts_synch_timer ${CMAKE_THREAD_LIBS_INIT})
