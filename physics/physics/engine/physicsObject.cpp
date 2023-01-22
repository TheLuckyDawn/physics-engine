#include "physicsObject.h"

/*
This is the constructor for the PhysicsObject class. It takes in three parameters: 
@param mass
@param radius 
@param verlet
*/
PhysicsObject::PhysicsObject(float m, float r, Vector2 position, Vector2 velocity, int shape)
{
    mass = m;
    radius = r;
    type = shape;
    verletCalculator = Verlet(position.x, velocity.x, 0, position.y, velocity.y, 0);
    verletCalculator.update();
    applyForce(Vector2(0,250*m));
    //force of gravity added by default
    //By default, up is the negative direction, and down is positive, and I am too lazy to change this, so it will remain that way
    //250 was the constant that felt like a good speed, it's not earth's g, but it is one that made the simulation work the best
    //all the calculations still work on this g however, so it is still physically accurate given a planet with this gravity
}

PhysicsObject::PhysicsObject()
{
    mass = 0;
    radius = 0;
    type = 0;
    verletCalculator = Verlet(0, 0, 0, 0, 0, 0);
}

/*
This calculates where the top left corner of the bounding box is, so that the renderer can correctly display the position of the object. All calculations use the center of the object as its "center of mass".
*/
Vector2 PhysicsObject::topLeftCorner()
{
    return Vector2(verletCalculator.getXPosition()-radius, verletCalculator.getYPosition()-radius);
}

/*
This adds a force to the list of forces acting upon an object.
*/
void PhysicsObject::applyForce(Vector2 force)
{
    forceArray.push_back(force);
}

/*
This method uses vector addition to add up all of the forces acting upon an object.
*/
Vector2 PhysicsObject::sumForces()
{
    Vector2 netForce = Vector2(0, 0);
    for (Vector2 force : forceArray)
    {
        netForce = netForce + force;
    }
    return netForce;
}

/*
This method updates acceleration in both the x and y direction based off of the net force in each direction. This is done using the Newton's second law equation.

Acceleration = (Net Force)/(Mass)
*/
void PhysicsObject::updateAcceleration()
{
    Vector2 netForce = sumForces();
    verletCalculator.setAcceleration(netForce.x/mass, Verlet::X);
    verletCalculator.setAcceleration(netForce.y/mass, Verlet::Y);
}

/*
This method updates the objects movement using Verlet integration, which is implemented is verlet.cpp.
*/
void PhysicsObject::updateMovement(float deltaTime)
{
    verletCalculator.setDeltaTime(deltaTime);
    updateAcceleration();
    verletCalculator.update();
}

void PhysicsObject::draw(sf::RenderWindow &window)
{
    if (type == PhysicsObject::square)
    {
        sf::RectangleShape rect(sf::Vector2f(radius*2, radius*2));
        rect.setPosition(sf::Vector2f(verletCalculator.getXPosition(), verletCalculator.getYPosition()));
        window.draw(rect);
    }
    else if (type == PhysicsObject::circle)
    {
        sf::CircleShape circ(radius);
        circ.setPosition(sf::Vector2f(verletCalculator.getXPosition(), verletCalculator.getYPosition()));
        window.draw(circ);
    }
}

Vector2 PhysicsObject::getPosition()
{
    return Vector2(verletCalculator.getXPosition(), verletCalculator.getYPosition());
}

Vector2 PhysicsObject::getVelocity()
{
    return Vector2(verletCalculator.getXVelocity(), verletCalculator.getYVelocity());
}

Vector2 PhysicsObject::getAcceleration()
{
    return Vector2(verletCalculator.getXAcceleration(), verletCalculator.getYAcceleration());
}