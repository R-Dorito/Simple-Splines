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
    if (n == 0){return 1;}
    return n * factorio(n - 1);
}

float binomials(int n, int i){
    //std::cout << "binomials hit" << std::endl;
    if (i > n)
        return 0;
  
  	// base condition when k and n are equal or k = 0
    if (i == 0 || i == n)
        return 1;
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

Vector2 bernstein(Ball P[], int n, float t){
    float resultX = 0.0f;
    float resultY = 0.0f;
    int nt = n-1;

    for(int i = 0; i < n; i++){
        resultX += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * P[i].pos.x;
        resultY += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * P[i].pos.y;
    }
    return {resultX, resultY};
}

Vector2 deCasteljau(Ball P[], int n, float t){

    Vector2 Q[n];

    for (int i = 0; i < n; i++) {
        Q[i] = P[i].pos; // P for point.
    } 

    for(int i = 0; i < n - 1; i++){ 
        // dont forget to check the "- 1", if the point starts at 0,0 or it's flying off somewhere, it's likely a -1 problem
        for(int j = 0; j < n - i - 1; j++){ 
            // reduce the number of itterations for each step. So reduce "i" over time
            Q[j].x = (Q[j].x * (1-t)) + (Q[j+1].x * t);
            Q[j].y = (Q[j].y * (1-t)) + (Q[j+1].y * t);
        }
    }

    return {Q[0]}; // this is the single point location after reducing all the balls on the 
}

void drawBezier(Ball balls[], int ballCount){
    Vector2 point = {0,0};
    Vector2 previousPoint = {balls[0].pos.x, balls[0].pos.y};
    
    for (float t = 0; t < 1.0f; t += 0.01f){
        //point = bernstein(balls, ballCount, t);
        point = deCasteljau(balls, ballCount, t);
        DrawLineEx(previousPoint, point, 5, RED); 
        previousPoint = point;
    }
}

void drawExistingBalls(Ball balls[], int ballNum){
    for (int i = 0; i < ballNum; i++)
    {
        DrawText(TextFormat("X: %i, Y: %i",(int)balls[i].pos.x, (int)balls[i].pos.y), balls[i].pos.x - 30, balls[i].pos.y - 20,5, RED);
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
        if(i > 0){
            //drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            //DrawLineEx(balls[i-1].pos, balls[i].pos, 1, GRAY);
            drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            drawBezier(balls, ballNum);
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
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
