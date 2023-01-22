#include "engine.h"

PhysicsObject* Engine::allObjs[10000];
int Engine::nextID = 0;

void Engine::update(float dt)
{
    for (int ind = 0; ind < 10000; ind++)
    {
        if (ind < nextID)
        {
            (*Engine::allObjs[ind]).updateMovement(dt);
            (*Engine::allObjs[ind]).updateAcceleration();
        }
        continue;
    }
}

void Engine::draw(sf::RenderWindow &window)
{
    for (int ind = 0; ind < 10000; ind++)
    {
        if (ind < nextID)
        {
            PhysicsObject obj = *Engine::allObjs[ind];
            obj.draw(window);
        }
        continue;
    }
}

void Engine::addToObjectPool(PhysicsObject& object)
{
    allObjs[nextID] = &object;
    (*allObjs[nextID]).ID = nextID;
    nextID++;
}