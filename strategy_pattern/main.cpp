#include <vector>
#include "shape.h"

using Shapes = std::vector<std::unique_ptr<Shape>>;

void drawAllShapes(const Shapes& shapes)
{
    for(const auto& shape: shapes)
    {
        shape->draw();
    }
}

int main()
{
    
    Shapes shapes;
    shapes.emplace_back(std::make_unique<Circle>(2.0, std::make_unique<OpenGLCircleDrawStrategy>()));
    shapes.emplace_back(std::make_unique<Square>(2.0, std::make_unique<OpenGLSquareDrawStrategy>()));

    drawAllShapes(shapes);
    return 0;
}