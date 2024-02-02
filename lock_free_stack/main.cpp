#include <iostream>
#include <thread>
#include <chrono>
#include "lock_free_stack.hpp"

lock_free_stack<int> int_stack;

void thread_entry_1()
{
    for(int i =0;i< 100; i++)
    {
        int_stack.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void thread_entry_2()
{
        for(int i =100;i< 200; i++)
    {
        int_stack.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int main()
{
    std::thread t1(thread_entry_1);
    std::thread t2(thread_entry_2);

    t1.join();
    t2.join();

    while(int_stack.is_empty() == false)
    {
        std::cout << int_stack.pop() << "\n";
    }
    return 0;
}