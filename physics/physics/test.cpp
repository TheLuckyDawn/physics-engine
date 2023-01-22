#include "engine/verlet.h"
#include <iostream>
using namespace std;
int main()
{
    Verlet rectangle(100.0, 10.0, 0.0, 400.0, 0.0, -10.0);
    cout << "X: " << rectangle.getXPosition() << ", Y: " << rectangle.getYPosition() << ", Prev X: " << rectangle.getPreviousXPosition() << std::endl;
    cout << "X Velocity: " << rectangle.getXVelocity() << " Y Velocity: " << rectangle.getYVelocity() << " X Acceleration: " << rectangle.getXAcceleration() << " Y Acceleration: " << rectangle.getYAcceleration() << std::endl;
    rectangle.setDeltaTime(0.01);
    for (int i = 0; i < 100; i++)
    {
        std::cout << "X: " << rectangle.getXPosition() << ", Y: " << rectangle.getYPosition() << std::endl;
        rectangle.update();
    }
    system("pause");
    return 0;
}
//command line actions:
//g++ -c test.cpp
//g++ test.o -o test