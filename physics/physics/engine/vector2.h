#ifndef VECTOR2_H
#define VECTOR2_H
class Vector2
{
    public:
        float x;
        float y;
        Vector2();
        Vector2(float initialX, float initialY);
        float getMagnitude();
        Vector2 getUnitVector();
        float dotProduct(const Vector2 vector);
        
        Vector2 operator+(const Vector2 vector);
        Vector2 operator-(const Vector2 vector);
        Vector2 operator*(const float scalar);
        Vector2 operator/(const float scalar);
        Vector2 operator*(const Vector2 vector);
};
#endif