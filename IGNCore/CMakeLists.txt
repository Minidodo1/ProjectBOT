cmake_minimum_required(VERSION 3.16.3)
project(IGNCore)
set(CMAKE_CXX_STANDARD 20)

add_executable(IGNCore main.cpp lookup/server_packet.cpp Slave.cpp EventService.cpp buddylist.cpp lookup/LookupService.cpp lookup/LookupService.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")
target_link_libraries(IGNCore aochat)
if (WIN32)
    target_link_libraries(IGNCore cygwin1 cyggcc_s-seh-1 crypto)
else ()
    target_link_libraries(IGNCore crypto)
endif (WIN32)
