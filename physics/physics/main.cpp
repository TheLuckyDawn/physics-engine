#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;
#include "engine/engine.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics Engine");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    sf::Font font;
    if (!font.loadFromFile("fonts/Roboto-Regular.ttf"))
    {
        window.setTitle("error!");
    }

    sf::Text text("Test String", font, 300);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f textPosition(300, 300);
    text.setPosition(textPosition);

    PhysicsObject rectangle(1000, 50, Vector2(600, 350), Vector2(50, 0), PhysicsObject::square);
    Engine::addToObjectPool(rectangle);
    PhysicsObject circle(10, 15, Vector2(100, 100), Vector2(0,0), PhysicsObject::circle);
    Engine::addToObjectPool(circle);
    //Verlet tester(Vector2(50,50), Vector2(10, 0), Vector2(0, 10));
    while (window.isOpen())
    {
        //setting delta time
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                //rectangle.updateMovement(deltaTime);
                //tester.update();
                float x = (*Engine::allObjs[0]).getVelocity().y;
                window.setTitle(std::to_string(x));
            };
        }
        
        
        //rendering

        window.clear();
        Engine::draw(window);
        //rectangle.draw(window);
        window.draw(text);
        window.display();
        //rectangle.updateMovement(deltaTime);
        Engine::update(deltaTime);
    }

    return 0;
}

//This is the command line to run the program (run in the terminal)
//mingw32-make

//mingw32-make clean (clears the object and exe file after use)