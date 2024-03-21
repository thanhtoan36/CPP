#pragma once
#include <memory>
#include "draw_strategy.h"

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual void draw() const = 0;
    virtual void serialize() const = 0;
};

class Circle : public Shape
{
public:
    Circle(double rad, std::unique_ptr<CircleDrawStrategy> draw_strategy);

    virtual void draw() const override;
    virtual void serialize() const override;

    double getRadius() const noexcept;
    void setRadius(const double &value);

private:
    double m_rad;
    std::unique_ptr<CircleDrawStrategy> m_drawing;
};

class Square : public Shape
{
public:
    Square(double dem, std::unique_ptr<SquareDrawStrategy> draw_strategy);

    virtual void draw() const override;
    virtual void serialize() const override;

    double getDim() const noexcept;
    void setDim(const double &value);

private:
    double m_dim;
    std::unique_ptr<SquareDrawStrategy> m_drawing;
};
