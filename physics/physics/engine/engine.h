#ifndef ENGINE
#define ENGINE
#include "physicsObject.h"
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;

class Engine
{
    private:
        static int nextID;
        
    public:
        static bool isTyping;
        static bool isPaused;
        static PhysicsObject* allObjs[];
        static void draw(sf::RenderWindow &window);
        static void update(float dt);
        static void pause();
        static void switchTypingMode();
        static void addToObjectPool(PhysicsObject& object);
        static int handleCollisionsObject(PhysicsObject object);
};
#endif