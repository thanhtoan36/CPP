#include "shape.h"

Circle::Circle(double rad, std::unique_ptr<CircleDrawStrategy> draw_strategy) : m_rad(rad), m_drawing(std::move(draw_strategy))
{
}

void Circle::draw() const
{
    m_drawing->draw(*this);
}

void Circle::serialize() const
{
}

double Circle::getRadius() const noexcept
{
    return m_rad;
}
void Circle::setRadius(const double &value)
{
    m_rad = value;
}

Square::Square(double dim, std::unique_ptr<SquareDrawStrategy> draw_strategy) : m_dim(dim), m_drawing(std::move(draw_strategy))
{
}

void Square::draw() const
{
    m_drawing->draw(*this);
}

void Square::serialize() const
{
}

double Square::getDim() const noexcept
{
    return m_dim;
}
void Square::setDim(const double &value)
{
    m_dim = value;
}