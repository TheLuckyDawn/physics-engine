#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;
#include "engine/vector2.h"
#include "engine/physicsObject.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics Engine");
    window.setFramerateLimit(60);
    sf::Clock clock;
    
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        window.setTitle("error!");
    }
    sf::Text text("Test String", font, 300);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f textPosition(300, 300);
    text.setPosition(textPosition);

    sf::RectangleShape rect;
    PhysicsObject rectangle(10, 25, Vector2(600, 350), Vector2(50, 0));

    rect.setSize(sf::Vector2f(100,100));

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
        }
        
        
        //rendering

        window.clear();
        window.draw(rect);
        window.draw(text);
        window.display();
        rectangle.updateMovement(deltaTime);
        rect.setPosition(sf::Vector2f(rectangle.topLeftCorner().x, rectangle.topLeftCorner().y));
    }

    return 0;
}

//This is the command line to run the program (run in the terminal)
//mingw32-make

//mingw32-make clean (clears the object and exe file after use)