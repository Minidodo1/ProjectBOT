cmake_minimum_required(VERSION 3.16.3)
project(ProjectBOT)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

set(CMAKE_CXX_STANDARD 20)
link_directories(/usr/local/lib/)
link_directories(/lib/)
link_directories(/bin/)

add_subdirectory(IGNCore)
