cmake_minimum_required(VERSION 3.18.4)
project(event_emitter)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} event.h event_emitter.h event_types.h main.cpp)