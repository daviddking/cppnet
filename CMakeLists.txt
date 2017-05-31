cmake_minimum_required(VERSION 3.7)
project(cppnet)

set(CMAKE_CXX_STANDARD 14)
#set(NETWORKING_TS_ROOT "/home/david/git/networking-ts-impl")
set(NETWORKING_TS_ROOT "/Users/dking/git/networking-ts-impl")

# Requires boost
# To install boost on Ubuntu:
#     sudo apt-get install libboost-all-dev
#find_package(Boost REQUIRED COMPONENTS date_time filesystem system)
#include_directories(${Boost_INCLUDE_DIRS})

find_package(Threads REQUIRED)

include_directories(${NETWORKING_TS_ROOT}/include)

add_executable(timer_sync timer_synch.cpp)
target_link_libraries(timer_sync ${CMAKE_THREAD_LIBS_INIT})

add_executable(timer_asynch timer_asynch.cpp)
target_link_libraries(timer_asynch ${CMAKE_THREAD_LIBS_INIT})

add_executable(timer_asynch_repeating timer_asynch_repeating.cpp)
target_link_libraries(timer_asynch_repeating ${CMAKE_THREAD_LIBS_INIT})

add_executable(timer_asynch_repeating2 timer_asynch_repeating2.cpp)
target_link_libraries(timer_asynch_repeating2 ${CMAKE_THREAD_LIBS_INIT})

add_executable(daytime_server_synch_tcp daytime_server_synch_tcp.cpp clion_syntax_highlight.h)
target_link_libraries(daytime_server_synch_tcp ${CMAKE_THREAD_LIBS_INIT})

add_executable(daytime_client_synch_tcp daytime_client_synch_tcp.cpp clion_syntax_highlight.h)
target_link_libraries(daytime_client_synch_tcp ${CMAKE_THREAD_LIBS_INIT})
