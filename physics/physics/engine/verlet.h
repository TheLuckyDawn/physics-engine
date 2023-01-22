#ifndef VERLET_H
#define VERLET_H
/*
@author yes!
*/
#include "vector2.h"
class Verlet
{
    private:
        float xAcceleration;
        float yAcceleration;
        float xVelocity;
        float yVelocity;
        float previousXPosition;
        float xPosition;
        float previousYPosition;
        float yPosition;
        static float dt;

    public:
        static int const X = 0;
        static int const Y = 1;
        Verlet();
        Verlet(Vector2 position, Vector2 velocity, Vector2 acceleration);
        Verlet(float initalXPosition, float initialXVelocity, float initialXAcceleration, float initialYPosition, float initialYVelocity, float initialYAcceleration);

        void update();
        float getXPosition();
        float getYPosition();
        float getPreviousXPosition();
        float getPreviousYPosition();
        float getXVelocity();
        float getYVelocity();
        float getXAcceleration();
        float getYAcceleration();
        float calculatePreviousPosition(int axis);
        float calculateNextPosition(int axis);
        float calculateNextVelocity(int axis);
        void setAcceleration(float newAcceleration, int axis);
        void setVelocity(float newVelocity, int axis);
        void setPosition(float newPosition, int axis);
        void setDeltaTime(float newDeltaTime);

};
#endif