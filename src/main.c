#include <raylib.h>
#include <raymath.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include "raycast.h"
#include <stdio.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif
Vector2 *pointA;
Vector2 *pointB;
int totalPoints = 2;
Ray2D ray;
RayCollision2D collision;
float radius = 20;
Vector2 circlePos = (Vector2){700, 300};
void UpdateDrawFrame(void);
Rectangle rect = {50, 50, 100, 75};
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    pointA = malloc(sizeof(Vector2));
    pointB = malloc(sizeof(Vector2));

    pointA[0] = (Vector2){300, 100};
    pointB[0] = (Vector2){200, 50};
    pointA[1] = (Vector2){200, 100};
    pointB[1] = (Vector2){400, 50};

    ray.position = (Vector2){screenWidth/2, screenHeight/2};

    InitWindow(screenWidth, screenHeight, "Raycast Test");
    #ifndef __EMSCRIPTEN__
        SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            UpdateDrawFrame();
        }

    #else
        emscripten_set_main_loop(UpdateDrawFrame, 0,1);
    #endif
    //--------------------------------------------------------------------------------------


    // De-Initialization
    //--------------------------------------------------------------------------------------
    free(pointA);
    free(pointB);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdateDrawFrame(void)
{
        // Main game loop
        ray.direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), ray.position));
        collision = GetRay2DCollisionRect(ray, rect);
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            rect.x = GetMousePosition().x;
            rect.y = GetMousePosition().y;
            printf("dir:%f, %f\n", ray.direction.x, ray.direction.y);
            printf("ln: %f,%f\n", Vector2Normalize(Vector2Subtract(collision.point, ray.position)).x,  Vector2Normalize(Vector2Subtract(collision.point, ray.position)).y);

        }
        // Update
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec(rect, RED);
            DrawCircleV(circlePos, radius, GREEN);
            if(collision.hit)
            {
                DrawCircleV(collision.point, 5, RED);
                DrawLineV(ray.position, collision.point, GREEN);     
       
            }                
            DrawLineV(ray.position, Vector2Add(ray.position, Vector2Multiply(ray.direction, (Vector2){10,10})), PURPLE);

        EndDrawing();
        //----------------------------------------------------------------------------------

}