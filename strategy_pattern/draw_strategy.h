#pragma once

class Circle;
class Square;

class CircleDrawStrategy
{
public:
    virtual ~CircleDrawStrategy() {}
    virtual void draw(const Circle &circle) const = 0;
};

class OpenGLCircleDrawStrategy : public CircleDrawStrategy
{
public:
    virtual void draw(const Circle &circle) const override;
};

class SquareDrawStrategy
{

public:
    virtual ~SquareDrawStrategy() {}
    virtual void draw(const Square &square) const = 0;
};

class OpenGLSquareDrawStrategy : public SquareDrawStrategy
{
public:
    virtual void draw(const Square &circle) const override;
};