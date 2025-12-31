#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"
#include "../headers/globals.h"

#include <iostream>
#include <cmath> 

//---global variables---
const int maxBalls = 100;
Ball balls[maxBalls]; 
int ballNum = 0;  
float startBallRadius = 10;
//-------

const int screenWidth = 800;
const int screenHeight = 600;

int degreeOfSpline = 1;

void clearScreen(){
    for (int i = 0; i < ballNum-1; i++) {
        balls[i] = {
            {0,0},
            0.0f,
            (Color){0, 0, 0, 255}
        };
    }
    ballNum = 0;
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "I love them curvy");
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
                ballNum--;
                if(degreeOfSpline > ballNum && degreeOfSpline > 1){
                    degreeOfSpline--;
                }
            }
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            clearScreen();
            degreeOfSpline = 1;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawExistingBalls(degreeOfSpline);
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);
            DrawText(TextFormat("BallNum: %d", ballNum), 0,15,5, BLACK);
            DrawText(TextFormat("Degree: %d", degreeOfSpline), 0,25,5, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
