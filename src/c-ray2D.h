#ifndef H_CRAY2D
#define H_CRAY2D

#include <stdbool.h>
#ifndef RL_RECTANGLE_TYPE
typedef struct Rectangle {
        float x;                // Rectangle top-left corner position x
        float y;                // Rectangle top-left corner position y
        float width;            // Rectangle width
        float height;           // Rectangle height
    } Rectangle;
#endif
#ifndef RL_VECTOR2_TYPE
    typedef struct Vector2 {
        float x;                // Vector x component
        float y;                // Vector y component
    } Vector2;
#endif

typedef struct Ray2D
{
    Vector2 position;
    Vector2 direction;
} Ray2D;

typedef struct RayCollision2D
{
    bool hit;
    float distance;
    Vector2 point;
} RayCollision2D;

RayCollision2D GetRay2DCollisionLine(Ray2D cast, Vector2 startPos, Vector2 endPos);
RayCollision2D GetRay2DCollisionLines(Ray2D cast, Vector2 *startPoints, Vector2 *endPoints, int totalBoundaries);
RayCollision2D GetRay2DCollisionPoly(Ray2D cast, Vector2 *points, int totalPoints);
RayCollision2D GetRay2DCollisionRect(Ray2D cast, Rectangle rect);
RayCollision2D GetRay2DCollisionTriangle(Ray2D cast, Vector2 p1, Vector2 p2, Vector2 p3);
RayCollision2D GetRay2DCollisionCircle(Ray2D cast, Vector2 circlePos, float radius);

#endif