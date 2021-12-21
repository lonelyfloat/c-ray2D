#include<math.h>
#include <stdlib.h>
#include "raycast.h"

RayCollision2D GetRay2DCollisionLine(Ray2D cast, Vector2 startPos, Vector2 endPos)
{    
    float offsetPositionX = cast.position.x + cast.direction.x;
    float offsetPositionY = cast.position.y + cast.direction.y;

    float denom = (startPos.x - endPos.x)*(cast.position.y-offsetPositionY) - (startPos.y - endPos.y)*(cast.position.x-offsetPositionX);
    if (denom == 0)
    {
        return (RayCollision2D){false, -1, (Vector2){0,0}};
    }
    float t = ((startPos.x - cast.position.x)*(cast.position.y - offsetPositionY) - (startPos.y-cast.position.y)*(cast.position.x-offsetPositionX)) / denom;
    float u = ((startPos.x - cast.position.x)*(startPos.y - endPos.y) - (startPos.y-cast.position.y)*(startPos.x - endPos.x)) / denom;
    if (t >= 0 && t <= 1 && u >= 0)
    {
        Vector2 point = (Vector2){startPos.x + t * (endPos.x-startPos.x),startPos.y + t * (endPos.y-startPos.y)};
        return (RayCollision2D){true, sqrtf((cast.position.x - point.x)*(cast.position.x - point.x) + (cast.position.y - point.y)*(cast.position.y - point.y)), point};
    }
    else
    {
        return (RayCollision2D){false, -1, (Vector2){0,0}};
    }
}

RayCollision2D GetRay2DCollisionLines(Ray2D cast, Vector2 *startPoints, Vector2 *endPoints, int totalBoundaries)
{    
    RayCollision2D closest;
    closest.hit = false;
    float shortestDist = 10000;
    for (int i = 0; i < totalBoundaries; ++i)
    {
        RayCollision2D collide = GetRay2DCollisionLine(cast, startPoints[i], endPoints[i]);
        if(collide.hit && (collide.distance < shortestDist))
        {
            shortestDist = collide.distance;
            closest = collide;
        } 
    }
    if (closest.hit)
    {
        return closest;
    }
    else return (RayCollision2D){false, -1, (Vector2){0,0}};
}

RayCollision2D GetRay2DCollisionPoly(Ray2D cast, Vector2 *points, int totalPoints)
{
    if (totalPoints >= 2 && points != NULL)
    {
        Vector2 *nextPoints = malloc(totalPoints * sizeof(Vector2));

        for (int i = 0; i < totalPoints-1; ++i)
        {
            nextPoints[i] = points[i + 1];
        }
        nextPoints[totalPoints-1] = points[0];
        RayCollision2D collide = GetRay2DCollisionLines(cast, points, nextPoints, totalPoints);
        free(nextPoints);
        return collide;
    }
    else return (RayCollision2D){false, -1, (Vector2){0,0}};
}

RayCollision2D GetRay2DCollisionRect(Ray2D cast, Rectangle rect)
{
    return GetRay2DCollisionPoly(cast, (Vector2[]){
        {rect.x, rect.y}, {rect.x + rect.width, rect.y}, {rect.x + rect.width, rect.y + rect.height}, {rect.x, rect.y + rect.height}
        },
     4);
}

RayCollision2D GetRay2DCollisionTriangle(Ray2D cast, Vector2 p1, Vector2 p2, Vector2 p3)
{
    return GetRay2DCollisionPoly(cast, (Vector2[]){p1, p2, p3}, 3);
}


RayCollision2D GetRay2DCollisionCircle(Ray2D cast, Vector2 circlePos, float radius)
{
    RayCollision2D result;
    Vector2 vecToPoint = (Vector2){circlePos.x - cast.position.x, circlePos.y - cast.position.y};
    
    float dot = (cast.direction.x*vecToPoint.x + cast.direction.y*vecToPoint.y);

    Vector2 nearestPoint = { cast.position.x + cast.direction.x * dot, cast.position.y + cast.direction.y * dot};

    float nearestDist = sqrtf((circlePos.x - nearestPoint.x)*(circlePos.x - nearestPoint.x) + (circlePos.y - nearestPoint.y)*(circlePos.y - nearestPoint.y));

    float b = sqrtf(radius * radius - nearestDist * nearestDist);

    result.distance = nearestDist - radius;
    result.point = (Vector2){cast.position.x + cast.direction.x * (dot-b), cast.position.y + cast.direction.y * (dot-b)};
    result.hit = nearestDist <= radius && sqrtf((vecToPoint.x*vecToPoint.x) + (vecToPoint.y*vecToPoint.y)) > sqrtf((cast.position.x - result.point.x)*(cast.position.x - result.point.x) + (cast.position.y - result.point.y)*(cast.position.y - result.point.y));
        
    if (result.hit) return result;
    else return (RayCollision2D){false, -1, (Vector2){0,0}}; 
}
