#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"

#include <iostream>
#include <cmath> 

const int screenWidth = 800;
const int screenHeight = 600;
float startBallRadius = 10;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Raylib 1 - Misc");
    SetTargetFPS(60);    

    Vector2 ballPosition = {0,0};

    while (!WindowShouldClose())   
    {
        ballPosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            balls[ballNum] = {
                ballPosition,
                startBallRadius,
                BLUE
            };
            ballNum++;
        }    

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            clearScreen();
        }
    
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawExistingBalls();

            //below is the current ball location
            DrawCircleV(ballPosition, startBallRadius, LIME);
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
