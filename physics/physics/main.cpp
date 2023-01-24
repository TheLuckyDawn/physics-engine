#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;
#include "engine/engine.h"
/*
This is the main function, where it all starts. There isn't much physics in here. Most of the physics happens in
verlet.cpp, AABB.cpp, and physicsObject.cpp. Don't worry about the .h files, my reflections are not in there.
If you want an overview of the functions without the implementations however, you can check them out.
*/
bool isANumber(std::string str) {
    for (int ind = 0; ind < str.length(); ind++)
    {
        const char character = str[ind];
        string period = ".";
        if (character == period[0] && ind < str.length() - 1)
        {
            continue;
        } else if (isdigit(character)) {
            continue;
        }
        return false;
    }
    return true;
}

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
    sf::Text position("Ball Position: ", font, 20);
    position.setFillColor(sf::Color::White);
    position.setPosition(10, 150);
    sf::Text velocity("Ball Velocity: ", font, 20);
    velocity.setFillColor(sf::Color::White);
    velocity.setPosition(10, 180);
    sf::Text text("Physics Engine: Ball Shooting Simulation", font, 60);
    text.setFillColor(sf::Color::White);
    sf::Vector2f textPosition(10, 10);
    text.setPosition(textPosition);

    //Shapes!
    Vector2 defaultPos(200, 400);
    PhysicsObject ground;
    Engine::addToObjectPool(ground);
    PhysicsObject circle(50, 50, defaultPos, Vector2(150, 0), PhysicsObject::circle);
    Engine::addToObjectPool(circle);
    sf::VertexArray circleTrail;
    circleTrail.setPrimitiveType(sf::PrimitiveType::LinesStrip);
    //Verlet tester(Vector2(50,50), Vector2(10, 0), Vector2(0, 10));
    while (window.isOpen())
    {
        //setting delta time
        window.clear();
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        string number = "";
        sf::Text userInserted("", font, 40);
        userInserted.setFillColor(sf::Color::White);
        sf::Vector2f text2Position(10, 80);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            if (event.type == sf::Event::KeyReleased) {
                //cheeky pause button
                if (event.key.code == sf::Keyboard::Space)
                {
                    Engine::pause();
                } 
                float scalar = 0;
                switch (event.key.code)
                {
                    case (sf::Keyboard::Num0):
                        scalar = 1;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num1):
                        scalar = 1.5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num2):
                        scalar = 2;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num3):
                        scalar = 2.5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num4):
                        scalar = 3;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num5):
                        scalar = 3.5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num6):
                        scalar = 4;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num7):
                        scalar = 4.5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num8):
                        scalar = 5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    case (sf::Keyboard::Num9):
                        scalar = 5.5;
                        circle.reset(defaultPos, Vector2(100*scalar, 0));
                        circleTrail.clear();
                        break;
                    default:
                        break;
                }
            }
        }
        
        
        //rendering

        window.setTitle(to_string(Engine::handleCollisionsObject(circle)));
        Engine::draw(window);
        position.setString("Position: " + to_string(circle.getPosition().x) + ", " + to_string(circle.getPosition().y));
        velocity.setString("Velocity: " + to_string(circle.getVelocity().x) + ", " + to_string(circle.getVelocity().y));
        //rectangle.draw(window);
        window.draw(circleTrail);
        window.draw(text);
        window.draw(position);
        window.draw(velocity);
        window.display();
        
        //rectangle.updateMovement(deltaTime);
        if (!Engine::isPaused)
        {
            Engine::update(deltaTime);
            circleTrail.append(sf::Vertex(sf::Vector2f(circle.getPosition().x, circle.getPosition().y)));
        }
    }

    return 0;
}

//Notes about running the code:

//For the sane:
//I have sent you a video of this running, it's too much of a hassle
//to set up the dependencies correctly for me to expect you to do it. It should be
//attached to the assignment on Canvas.

//You can also try running the exe in the ZIP folder I uploaded to canvas. If this doesn't work,
//I promise it runs on my end. The only things that should be in the ZIP are the font folder and
//the exe file.

//I used SFML v. 2.5.1 (32 bit) for the graphical components, if you were curious.

//For masochists:
//If you REALLY wanted to run it, and the top option didn't work, you would need to install SFML to the right directory
//Your includePath variable would also need to be correct. You would also need a C++ compiler
//to compile the code, and you would need to compile everything in the correct order.
//You can check the makefile on github for the order that I used to get it to work.
//Additionally, you would need to clone the repo from github or manually download the ZIP.

//Github Link:
//https://github.com/Swordlord12/physics-engine

//This is the command line to compile the program (in the terminal)
//mingw32-make

//This is the command line to clear all of the .o and .exe files in the main directory
//mingw32-make clean (clears the object and exe file after use)

//You can run by double clicking the .exe file in file explorer.