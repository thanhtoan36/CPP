cmake_minimum_required(VERSION 3.18.4)
project(lock_free_stack)
set(CMAKE_CXX_STANDARD 17)

add_executable(lock_free_stack lock_free_stack.hpp main.cpp)
find_package (Threads)
target_link_libraries (lock_free_stack ${CMAKE_THREAD_LIBS_INIT})