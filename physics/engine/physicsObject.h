#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H
#include "verlet.h"
#include "vector2.h"
#include <list>
using namespace std;

class PhysicsObject
{
    private:
        float mass;
        float radius; //if square, this is 1/2 the length of one side
        Verlet verletCalculator;
        int type;
        list<Vector2> forceArray;

    public:
        static const int circle = 0;
        static const int square = 1;

        PhysicsObject(float m, float r, Vector2 position, Vector2 velocity);

        float getMass();

        Vector2 topLeftCorner();
        
        Vector2 getPosition();
        Vector2 getVelocity();
        Vector2 getAcceleration();
        Vector2 sumForces();
        void updateAcceleration();
        void updateMovement(float deltaTime);
        void applyForce(Vector2 force);
        void removeForce(Vector2 force);

};
#endif