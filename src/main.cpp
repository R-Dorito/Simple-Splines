#include "raylib.h"
#include "../headers/maths-2D.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"
#include "../headers/globals.h"

#include <iostream>
#include <cmath> 

//---global variables---
const int maxBalls = 100;
Ball balls[maxBalls]; 
Ball_3D balls_3d[maxBalls]; 
int ballNum = 0;  
float startBallRadius = 10.0f;
//-------

const int screenWidth = 800;
const int screenHeight = 600;

int degreeOfSpline = 1;

int isOver = -1;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "I love them curvy");
    SetTargetFPS(60);    

    Vector2 mouseLocation = {0,0};

    while (!WindowShouldClose())   
    {
        mouseLocation = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            isOver = -1;

            for (int i = ballNum - 1; i >= 0; i--)
            {
                if (CheckCollisionPointCircle(mouseLocation, balls[i].pos, balls[i].radius))
                {
                    isOver = i;
                    break;
                }
            }

            if (isOver == -1 && ballNum < maxBalls)
            {
                balls[ballNum++] = {
                    mouseLocation,
                    startBallRadius,
                    BLUE
                };
            }
        }    
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isOver != -1)
        {
            balls[isOver].pos = mouseLocation;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isOver = -1;
        }

        if(IsKeyReleased(KEY_W)){
            if(degreeOfSpline < ballNum - 1){
                degreeOfSpline++;
            }
        }
        if(IsKeyReleased(KEY_S)){
            if(degreeOfSpline > 1){
                degreeOfSpline--;
            }
        }
        if(IsKeyReleased(KEY_Z)){
            if(ballNum > 0){
                balls[ballNum] = {
                    {0,0},
                    0.0f,
                    (Color){0, 0, 0, 255}
                };

            if(degreeOfSpline > 1 && ballNum - 1 == degreeOfSpline){
                degreeOfSpline--;
            }

            ballNum--;
            }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            for (int i = 0; i < ballNum-1; i++) {
                balls[i] = {
                    {0,0},
                    0.0f,
                    (Color){0, 0, 0, 255}
                };
            }
            ballNum = 0;
            degreeOfSpline = 1;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawExistingBalls_2D(degreeOfSpline, mouseLocation);
            DrawText(TextFormat("X: %.0f, Y: %.0f",mouseLocation.x, mouseLocation.y), 0,0,5, BLACK);
            DrawText(TextFormat("BallNum: %d", ballNum), 0,15,5, BLACK);
            DrawText(TextFormat("Degree: %d", degreeOfSpline), 0,25,5, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
