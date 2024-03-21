#include <iostream>
#include "draw_strategy.h"
#include "shape.h"

void OpenGLCircleDrawStrategy::draw(const Circle &circle) const
{
    std::cout << "OpenGLCircleDrawStrategy"
              << "\n";
}

void OpenGLSquareDrawStrategy::draw(const Square &circle) const
{
    std::cout << "OpenGLSquareDrawStrategy"
              << "\n";
}