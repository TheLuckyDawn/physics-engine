#include "physicsObject.h"
/*
----------------------Reflection (all methods of this class)----------------------
This is the class that encapsulates a simulated physical object in the engine. Currently it only handles circles and squares due
to the difficulty of including other more complex shapes (especially concave ones). Each object has a mass, a Verlet Calculator
(which handles all of the kinematics of the object), a radius, and a type. The most important part of this class is the interaction
with forces with Newton's second law. This allows for the kinematics to be influenced by outside forces, rather than being stuck simulating
with the initial preset values. While just using the Verlet class would work for UAM simulations that Physics I uses, it would not provide a
realistically working physics engine and would not be able to compute the forces, instead needing the immediate net acceleration.
Another important aspect of this class is the collisions. Objects in reality do not exist within each other (I hope), and so it is important to
make sure objects do not phase through each other. I do this by using Axis-Aligned Bounding Boxes (AABB), which basically are rectangles that are
used as a 'hitbox' for the object. If this AABB intersects with any other AABB, then the objects need to have collision simulated between them.
This process is VERY expensive (O(n^2) if you know Big O notation), however for a small scale engine like this, it will work fine. If you were using
this engine on a bigger scale, you would need to optimize the algorithim.
*/

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
    applyForce(Vector2(0,250*m));
    axisAlignedBox = AABB(Vector2(position.x-r, position.y-r), Vector2(position.x+r, position.y+r));
    //force of gravity added by default
    //By default, up is the negative direction, and down is positive, and I am too lazy to change this, so it will remain that way
    //250 was the constant that felt like a good speed, it's not earth's g, but it is one that made the simulation work the best
    //all the calculations still work on this g however, so it is still physically accurate given a planet with this gravity
}

void PhysicsObject::reset(Vector2 position, Vector2 velocity)
{
    verletCalculator = Verlet(position.x, velocity.x, 0, position.y, velocity.y, 0);
}

PhysicsObject::PhysicsObject() // I use this for ground
{
    mass = 100000000;
    radius = 1000;
    type = 1;
    verletCalculator = Verlet(400, 0, 0, 1700, 0, 0);
    axisAlignedBox = AABB(Vector2(verletCalculator.getXPosition()-radius, verletCalculator.getYPosition()-radius), Vector2(verletCalculator.getXPosition()+radius, verletCalculator.getYPosition()+radius));
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
        netForce.x += force.x;
        netForce.y += force.y;
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

float PhysicsObject::getMass()
{
    return mass;
}
/*
This method updates the objects movement using Verlet integration, which is implemented is verlet.cpp.
*/
void PhysicsObject::updateMovement(float deltaTime)
{
    verletCalculator.setDeltaTime(deltaTime);
    updateAcceleration();
    verletCalculator.update();
    axisAlignedBox.updateBox(Vector2(verletCalculator.getXPosition()-radius, verletCalculator.getYPosition()-radius), Vector2(verletCalculator.getXPosition()+radius, verletCalculator.getYPosition()+radius));
}

void PhysicsObject::draw(sf::RenderWindow &window)
{
    if (type == PhysicsObject::square)
    {
        sf::RectangleShape rect(sf::Vector2f(radius*2, radius*2));
        rect.setPosition(sf::Vector2f(topLeftCorner().x, topLeftCorner().y));
        window.draw(rect);
    }
    else if (type == PhysicsObject::circle)
    {
        sf::CircleShape circ(radius);
        circ.setPosition(sf::Vector2f(topLeftCorner().x, topLeftCorner().y));
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