#include "verlet.h"

float Verlet::dt = 0.01;

Verlet::Verlet(float initialXPosition, float initialXVelocity, float initialXAcceleration, float initialYPosition, float initialYVelocity, float initialYAcceleration)
{
    setDeltaTime(1.0/60.0);
    xPosition = initialXPosition;
    xVelocity = initialXVelocity;
    xAcceleration = initialXAcceleration;
    previousXPosition = calculatePreviousPosition(Verlet::X);
    yPosition = initialYPosition;
    yVelocity = initialYVelocity;
    yAcceleration = initialYAcceleration;
    previousYPosition = calculatePreviousPosition(Verlet::Y);
}

Verlet::Verlet(Vector2 position, Vector2 velocity, Vector2 acceleration)
{
    setDeltaTime(1.0/60.0);
    xPosition = position.x;
    xVelocity = velocity.x;
    xAcceleration = acceleration.x;
    yPosition = position.y;
    yVelocity = velocity.y;
    yAcceleration = acceleration.y;
    previousXPosition = calculatePreviousPosition(Verlet::X);
    previousYPosition = calculateNextPosition(Verlet::Y);
}

Verlet::Verlet()
{
    xPosition = 600.0;
    yPosition = 350.0;
    xVelocity = 10.0;
    yVelocity = 10.0;
    xAcceleration = 0.0;
    yAcceleration = 0.0;
    setDeltaTime(1.0/60.0);
    previousXPosition = xPosition - xVelocity*dt + (1.0f/2.0f)*xAcceleration*dt*dt;
    previousYPosition =  yPosition - yVelocity*dt + (1.0f/2.0f)*yAcceleration*dt*dt;
}

void Verlet::update()
{
    float newXPosition = 2*xPosition - previousXPosition + xAcceleration*dt*dt;
    float newYPosition = 2*yPosition - previousYPosition + yAcceleration*dt*dt;
    float newXVelocity = calculateNextVelocity(Verlet::X);
    float newYVelocity = calculateNextVelocity(Verlet::Y);
    previousXPosition = xPosition;
    xPosition = newXPosition;
    previousYPosition = yPosition;
    yPosition = newYPosition;
    xVelocity = newXVelocity;
    yVelocity = newYVelocity;
}

float Verlet::calculatePreviousPosition(int axis)
{
    float newPosition;
    if (axis == Verlet::X)
    {
        newPosition = xPosition - xVelocity*dt + (1.0f/2.0f)*xAcceleration*dt*dt;
    }
    else
    {
        newPosition = yPosition - yVelocity*dt + (1.0f/2.0f)*yAcceleration*dt*dt;
    }
    return newPosition;
}

float Verlet::calculateNextPosition(int axis)
{
    float newPosition;
    if (axis == Verlet::X)
    {
        newPosition = 2*xPosition - previousXPosition + xAcceleration*dt*dt;
    }
    else
    {
        newPosition = 2*yPosition - previousYPosition + yAcceleration*dt*dt;
    }
    return newPosition;
}

float Verlet::calculateNextVelocity(int axis)
{
    float newVelocity;
    if (axis == Verlet::X)
    {
        newVelocity = xAcceleration*dt + xVelocity;
    }
    else
    {
        newVelocity = yAcceleration*dt + yVelocity;
    }
    return newVelocity;
}

void Verlet::setAcceleration(float newAcceleration, int axis)
{
    if (axis == Verlet::X)
    {
        xAcceleration = newAcceleration;
    } 
    else 
    {
        yAcceleration = newAcceleration;
    }
    
}

void Verlet::setVelocity(float newVelocity, int axis)
{
    if (axis == Verlet::X)
    {
        xVelocity = newVelocity;
    } 
    else 
    {
        yVelocity = newVelocity;
    }
}

void Verlet::setPosition(float newPosition, int axis)
{
    if (axis == Verlet::X)
    {
        xPosition = newPosition;
    } 
    else 
    {
        yPosition = newPosition;
    }
}

void Verlet::setDeltaTime(float newDeltaTime)
{
    dt = newDeltaTime;
}

float Verlet::getXPosition()
{
    return xPosition;
}

float Verlet::getYPosition()
{
    return yPosition;
}

float Verlet::getXVelocity()
{
    return xVelocity;
}

float Verlet::getYVelocity()
{
    return yVelocity;
}

float Verlet::getXAcceleration()
{
    return xAcceleration;
}

float Verlet::getYAcceleration()
{
    return yAcceleration;
}

float Verlet::getPreviousXPosition()
{
    return previousXPosition;
}

float Verlet::getPreviousYPosition()
{
    return previousYPosition;
}
