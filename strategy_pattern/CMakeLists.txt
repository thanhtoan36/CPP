cmake_minimum_required(VERSION 3.18.4)
project(strategy_pattern)
set(CMAKE_CXX_STANDARD 17)
add_executable(strategy_pattern draw_strategy.cpp shape.cpp main.cpp)