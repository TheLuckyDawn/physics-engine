#ifndef AABB_H
#define AABB_H
#include "vector2.h"
class AABB {
    private:
        Vector2 bottomLeft;
        Vector2 topRight;
    public:
        AABB(Vector2 bL, Vector2 tR);
        AABB();
        void updateBox(Vector2 bL, Vector2 tR);
        int testCollision(AABB otherObject);
};
#endif