#include <iostream>
#include "subject.hpp"

using MySubject = Subject<int, std::string>;

void fun0(int x, std::string s)
{
    std::cout << "fun0: " << x << " " << s << std::endl;
}


class IObserver
{
public:
    virtual void fun(int x, std::string s) = 0;
    IObserver(MySubject &s)
    {
        m_funtor = s.makeObserver(std::bind(&IObserver::fun, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    std::shared_ptr<std::function<void(int x, std::string s)>> m_funtor;
};

class Observer1 : public IObserver
{
public:
    Observer1(MySubject &s) : IObserver(s)
    {

    }
    void fun(int x, std::string s) override
    {
        std::cout << "fun1: " << x << " " << s << std::endl;
    }
};

class Observer2 : public IObserver
{
public:
    Observer2(MySubject &s) : IObserver(s)
    {

    }
    void fun(int x, std::string s) override
    {
        std::cout << "fun2: " << x << " " << s << std::endl;
    }
};

int main()
{
    MySubject s;
    Observer1 a{s};    
    s.notify(0, "notify 1");
    {
        Observer2 b{s};
        s.notify(1, "notify 2");
    }
    s.notify(2, "notify 3");
}