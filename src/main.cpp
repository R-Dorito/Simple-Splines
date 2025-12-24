#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"

#include <iostream>
#include <cmath> 

#define MAX_BALLS 5000

const int screenWidth = 800;
const int screenHeight = 600;

int main(void)
{
    Ball balls[MAX_BALLS]; 
    int ballNum = 0;    
    float startBallRadius = 10;

    InitWindow(screenWidth, screenHeight, "Raylib 1 - Misc");
    SetTargetFPS(60);    

    Vector2 ballPosition = {0,0};

    while (!WindowShouldClose())   
    {
        if (IsKeyPressed(KEY_H))
        {
            if (IsCursorHidden()) {ShowCursor();}
            else HideCursor();
        }

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
    
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawExistingBalls(balls, ballNum);

            //below is the current ball location
            DrawCircleV(ballPosition, startBallRadius, LIME);
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
