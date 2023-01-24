#include "AABB.h"
/*
--------------------Reflection (all methods of this class)----------------------
Axis-Aligned Bounding Boxes are a way that some physics engines use to simply and condense the handling of collisions.
It allows for the engine to first check whether some objects COULD be colliding, and then checks if they are ACTUALLY colliding.
This helps more with more complex shapes, when you have more than just squares and circles. However, it does allow me to better scale
up this engine in the future if I desire. 
To check if two objects COULD be colliding with this method, you check whether the difference between the extreme values of the AABB
are greater than zero. If it is greater than zero, they cannot be colliding because there is some distance between the two objects. You
have to be careful however, as you want the collision to ONLY happen when NONE of the differences are greater than zero. This is because
two objects could be at the same height in the plane without being at the same x-values, and vice versa. It is also important to subtract
opposite sides of the object, as the extreme end could be colliding with the object without the other side colliding. This is also the reason
why you have to do 2 checks for each axis. One to check one object's top right corner vs the other's bottom left, and the other to check vice
versa (only for the coordinate of that axis for each calculation).  
*/

AABB::AABB(Vector2 bL, Vector2 tR)
{
    bottomLeft = bL;
    topRight = tR;
}

AABB::AABB()
{
    bottomLeft = Vector2(0,0);
    topRight = Vector2(0,0);
}

void AABB::updateBox(Vector2 bL, Vector2 tR)
{
    bottomLeft = bL;
    topRight = tR;
}

int AABB::testCollision(AABB otherObject)
{
    //https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects 
    //used a similar idea to there for collisions
    float diffX1 = otherObject.bottomLeft.x-topRight.x;
    float diffY1 = otherObject.bottomLeft.y-topRight.y;
    float diffX2 = bottomLeft.x-otherObject.topRight.x;
    float diffY2 = bottomLeft.y-otherObject.topRight.y;

    if (diffX1 > 0 || diffY1 > 0)
    {
        return 0;
    }

    if (diffX2 > 0 || diffY2 > 0)
    {
        return 0;
    }
    
    if (diffX1 < diffY1 && diffX2 < diffY2)
    {
        return 1;//x axis
    } else {
        return 2;//y axis
    }
}