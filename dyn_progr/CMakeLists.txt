cmake_minimum_required(VERSION 3.10)
project(dyn_progr)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

add_executable(dyn_progr main.cpp)