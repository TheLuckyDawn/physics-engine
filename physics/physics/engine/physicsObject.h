#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
#include "verlet.h"
#include "AABB.h"
#include "vector2.h"
#include <SFML/Graphics.hpp>
#include <list>
using namespace std;

class PhysicsObject
{
    private:
        float mass;
        float radius; //if square, this is 1/2 the length of one side
        int type;
        list<Vector2> forceArray;

    public:
        AABB axisAlignedBox;
        Verlet verletCalculator;
        static const int circle = 0;
        static const int square = 1;
        int ID;

        PhysicsObject(float m, float r, Vector2 position, Vector2 velocity, int shape);
        PhysicsObject();

        float getMass();

        Vector2 topLeftCorner();
        Vector2 getPosition();
        Vector2 getVelocity();
        Vector2 getAcceleration();
        Vector2 sumForces();
        void reset(Vector2 position, Vector2 velocity);
        void draw(sf::RenderWindow &window);
        void updateAcceleration();
        void updateMovement(float deltaTime);
        void applyForce(Vector2 force);
        void removeForce(Vector2 force);

};
#endif