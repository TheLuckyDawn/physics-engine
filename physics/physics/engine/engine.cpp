#include "engine.h"

PhysicsObject* Engine::allObjs[10000];
bool Engine::isPaused = true;
bool Engine::isTyping = false;
int Engine::nextID = 0;
/*
Physics down in the "handleCollisions" function
*/

void Engine::update(float dt)
{
    for (int ind = 0; ind < 10000; ind++)
    {
        if (ind < nextID)
        {
            (*Engine::allObjs[ind]).updateMovement(dt);
            (*Engine::allObjs[ind]).updateAcceleration();
        } else {
            break;
        }
    }
}

void Engine::draw(sf::RenderWindow &window)
{
    for (int ind = 0; ind < 10000; ind++)
    {
        if (ind < nextID)
        {
            (*Engine::allObjs[ind]).draw(window);
        } else {
            break;
        }
    }
}

void Engine::addToObjectPool(PhysicsObject& object)
{
    allObjs[nextID] = &object;
    (*allObjs[nextID]).ID = nextID;
    nextID += 1;
}

void Engine::pause()
{
    isPaused = !isPaused;
}

void Engine::switchTypingMode()
{
    isTyping = !isTyping;
}

/*
* This function checks for a collision with each object that exists within the simulation.

---------------Reflection----------------
This function assumes that all collisions are elastic: meaning that momentum and kinetic energy are conserved.
Using this, whenever the object passed into this function collides with another object, I reverse the direction
of it's velocity. This preserves momentum with the equation p = mv, as the velocity scalar remains constant, and
I am assuming that the rest of the objects of the simulation are massless (the ground). If I were to return
to this later, I would clean it up to make it work with more than just the ground and one object, and allow for
multi-object collisions that comply with the law of conservation of momentum.
*/
int Engine::handleCollisionsObject(PhysicsObject object)
{
    int colliding = -1;
    for (int ind = 0; ind < 10000; ind++)
    {
        if (ind < nextID)
        {
            if (ind != object.ID)
            {
                int collision = object.axisAlignedBox.testCollision((*Engine::allObjs[ind]).axisAlignedBox);
                if (collision != 0)
                {
                    colliding = collision;
                    if (collision == 1)
                    {
                        (*allObjs[object.ID]).reset(Vector2(object.getPosition().x, object.getPosition().y), Vector2(-(object.getVelocity().x), object.getVelocity().y)); 
                    }
                    else if (collision == 2)
                    {  
                        (*allObjs[object.ID]).reset(Vector2(object.getPosition().x, object.getPosition().y), Vector2(object.getVelocity().x, -(object.getVelocity().y)));
                        //the reason I have to reset the Verlet is so that the changes in Velocity kick in.
                    }
                }
            }
            continue;
        } else {
            break;
        }
    }
    return colliding;
}