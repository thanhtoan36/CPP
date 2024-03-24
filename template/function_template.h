#pragma once
#include <iostream>

template <typename T>
T mymax(T a, T b)
{
    return a < b ? b : a;
}

class Circle
{
public:
    Circle() = default;
    Circle(const double &r) : rad{r}
    {
    }
    Circle(Circle &other)
    {
        rad = other.getRad();
    }
    Circle &operator=(const Circle &other)
    {
        rad = other.getRad();
        return *this;
    }
    Circle(Circle &&other)
    {
        rad = other.getRad();
    }
    Circle &operator=(const Circle &&other)
    {
        rad = other.getRad();
        return *this;
    }
    ~Circle() = default;

    bool operator<(const Circle &other)
    {
        return this->getRad() < other.getRad();
    }

    friend std::ostream& operator<<(std::ostream& o, const Circle& sample)
    {
        o << "Circle rad: ";
        o << sample.getRad();
        return o;
    }

    double getRad() const noexcept
    {
        return rad;
    }

private:
    double rad{};
};