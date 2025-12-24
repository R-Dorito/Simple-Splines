#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"

#include <iostream>
#include <cmath> 

void drawLinearInterprolation(Vector2 p1, Vector2 p2){
    //float pointY;
    for (float i = 0; i < 1; i += 0.01f)
    {
        float x = p1.x + i * (p2.x - p1.x); //Interpolation Formula
        float y = p1.y + i * (p2.y - p1.y);
        
        DrawPixel((int)x, (int)y, RED);
    }
}

void drawBezier(Ball balls[], int n){
    Vector2 point = {0,0};
    Vector2 previousPoint = {balls[0].pos.x, balls[0].pos.y};
    
    for (float t = 0; t < 1.0f; t += 0.01f){
        //point = bernstein(balls, ballCount, t);
        point = deCasteljau(balls, n, t);
        DrawLineEx(previousPoint, point, 5, RED); 
        previousPoint = point;
    }
}

void drawExistingBalls(Ball balls[], int n){
    for (int i = 0; i < n; i++)
    {
        DrawText(TextFormat("X: %i, Y: %i",(int)balls[i].pos.x, (int)balls[i].pos.y), balls[i].pos.x - 30, balls[i].pos.y - 20,5, RED);
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
        if(i > 0){
            //drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            //DrawLineEx(balls[i-1].pos, balls[i].pos, 1, GRAY);
            drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            drawBezier(balls, n);
        }
    }
}