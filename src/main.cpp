#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"

#include <iostream>
#include <cmath> 

const int screenWidth = 800;
const int screenHeight = 600;
Color mouseDrawMode = LIME;
Color mouseDown = PINK;


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Raylib 1 - Misc");
    SetTargetFPS(60);    

    Vector2 ballPosition = {0,0};

    while (!WindowShouldClose())   
    {
        ballPosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_SPACE))
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
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
