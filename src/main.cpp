#include "raylib.h"
#include <iostream>

#define MAX_BALLS 5000

typedef struct  Ball {
    Vector2 pos;
    float radius;
    Color colour;
} Ball;


void drawExistingBalls(Ball balls[], int ballNum){
    for (int i = 0; i < ballNum; i++)
    {
        if(i > 0)
        {
            DrawLineV(balls[i-1].pos, balls[i].pos, BLACK);
            std::cout << "ball first " << i-1 << " and second " << i << std::endl;        
        }
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
    }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib 1 - Misc");
    SetTargetFPS(60);    

    int ballNum = 0;    
    Ball balls[MAX_BALLS]; 
    float startBallRadius = 5;
    
    Vector2 ballPosition = {
        (float) screenWidth / 2,
        (float) screenHeight / 2,
    };

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
            std::cout << "Num balls: " << ballNum << 
                " position x: "<< ballPosition.x <<
                " position y: "<< ballPosition.y <<
            std::endl;
        }    
    
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawExistingBalls(balls, ballNum);
            DrawCircleV(ballPosition, startBallRadius, BLUE);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
