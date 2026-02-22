cmake_minimum_required(VERSION 3.10)
project(CANInjector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(can_injector src/main.cpp src/CANClient.cpp)
