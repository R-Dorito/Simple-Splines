#include "raylib.h"
#include <iostream>
#include <cmath> 

#define MAX_BALLS 5000

typedef struct  Ball {
    Vector2 pos;
    float radius;
    Color colour;
} Ball;

float factorio(int n){
    if (n <= 1){return 1;}
    return n * factorio(n - 1);
}

float binomials(int n, int i){
    return factorio(n) / (factorio(i) * factorio(n-i));
}

void drawLinearInterprolation(Vector2 v1, Vector2 v2){
    //float pointY;
    for (float i = 0; i < 1; i += 0.01f)
    {
        float x = v1.x + i * (v2.x - v1.x); //Interpolation Formula
        float y = v1.y + i * (v2.y - v1.y);
        
        DrawPixel((int)x, (int)y, RED);
    }
}

float calcsTestX(Ball balls[], int n, int i, int t){
    float bio = binomials(n,i);
    float t_Pain = pow(t,i);
    float i_t = 0.0f;

    if(n > 0){i_t = pow((1-t), n-1);}
    else {i_t = 1;}

    return bio * t_Pain * i_t * balls[i].pos.x + calcsTestX(balls, n-1, i++, t);
}

float calcsTestY(Ball balls[], int n, int i, float t){
    float bio = binomials(n,i);
    float t_Pain = (float)pow(t,i);
    float i_t = 0.0f;

    if(n > 0){i_t = (float)pow((1-t), n-1);}
    else {i_t = 1;}

    return bio * t_Pain * i_t * balls[i].pos.y + calcsTestY(balls, n-1, i++, t);
}

void drawBezier(Ball balls[], int ballCount){
    Vector2 point;

    for (float t = 0; t < 1.0f; t += 0.005f){
        // point.x = (1 - t) * (1 - t) * (1 - t) * p1.x 
        //     + 3 * (1 - t) * (1 - t) * t * p2.x 
        //     + 3 * (1 - t) * t * t * p3.x 
        //     + t * t * t * p4.x;
        // point.y = (1 - t) * (1 - t) * (1 - t) * p1.y 
        //     + 3 * (1 - t) * (1 - t) * t * p2.y 
        //     + 3 * (1 - t) * t * t * p3.y 
        //     + t * t * t * p4.y;
        point.x = calcsTestX(balls, ballCount, 0, t);
        point.y = calcsTestX(balls, ballCount, 0, t);
        DrawCircleV(point, 2, RED); 
    }
}

void drawExistingBalls(Ball balls[], int ballNum){
    for (int i = 0; i < ballNum; i++)
    {

        
        drawBezier(balls, ballNum);
        
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
        if(i > 0){
            //drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            DrawLineEx(balls[i-1].pos, balls[i].pos, 2, BLUE);
        }
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
    float startBallRadius = 10;
    
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
        }    
    
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawExistingBalls(balls, ballNum);

            //below is the current ball location
            DrawCircleV(ballPosition, startBallRadius, LIME);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
