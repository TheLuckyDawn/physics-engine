#ifndef ENGINE
#define ENGINE
#include "physicsObject.h"
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;

class Engine
{
    private:
        static int menuID;
        static int nextID;
        
    public:
        static PhysicsObject* allObjs[];
        static void draw(sf::RenderWindow &window);
        static void update(float dt);
        static void changeState();
        static void addToObjectPool(PhysicsObject& object);
};
#endif