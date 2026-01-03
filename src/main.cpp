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
bool selectionMode = false;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "I love them curvy");
    SetTargetFPS(60);    

    Vector2 ballPosition = {0,0};

    while (!WindowShouldClose())   
    {
        ballPosition = GetMousePosition();

        if(IsKeyPressed(KEY_SPACE)){
            selectionMode = !selectionMode;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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

                //fix this later
                if(degreeOfSpline > 1){
                    std::cout << "deg of spline function being hit. deg: "<< degreeOfSpline << " balls " <<  ballNum << std::endl;                    
                    if(ballNum - 1 == degreeOfSpline){
                        std::cout << "if(ballNum == degreeOfSpline + 1) being hit" << std::endl;
                        degreeOfSpline--;
                    }
                    else if(ballNum - 1  > degreeOfSpline +1){
                        std::cout << "Else statment being hit" << std::endl;
                    }
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
            drawExistingBalls(degreeOfSpline);
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);
            DrawText(TextFormat("BallNum: %d", ballNum), 0,15,5, BLACK);
            DrawText(TextFormat("Degree: %d", degreeOfSpline), 0,25,5, BLACK);
            if(selectionMode){
                DrawText(TextFormat("Selection Mode"), screenWidth/2 - 75, 20, 20, RED);
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
