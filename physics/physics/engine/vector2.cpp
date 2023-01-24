#include "vector2.h"
#include <cmath>

/*
This is just my own implementation of Vector2s, you can laugh at how overcomplicated it is.
I do not know why I didn't just use a struct, or the built-in version. But hey, it's here!
There isn't much to do with physics, other than the fact that certain physics concepts use
vectors to work. That code isn't in here, though.
*/
Vector2::Vector2(float initialX, float initialY)
{
    x = initialX;
    y = initialY;
}

Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2 Vector2::operator+(const Vector2 vector)
{
    return Vector2(vector.x+x, vector.y+y);
}

Vector2 Vector2::operator-(const Vector2 vector)
{
    return Vector2(x-vector.x, y-vector.y);
}

Vector2 Vector2::operator*(const float scalar)
{
    return Vector2(x*scalar, y*scalar);
}

Vector2 Vector2::operator/(const float scalar)
{
    return Vector2(x/scalar, y/scalar);
}

float Vector2::dotProduct(const Vector2 vector)
{
    return x*vector.x + y*vector.y;
}

float Vector2::getMagnitude()
{
    return sqrt(x*x + y*y);
}

Vector2 Vector2::getUnitVector()
{
    return Vector2(x, y)/getMagnitude();
}