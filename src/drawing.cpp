#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"

#include <stdlib.h>   
#include <iostream>
#include <cmath> 
#include <ctime> 

float drawingRefreshRate = 0.05f;

Color getNewColour(){
    srand(static_cast<unsigned int>(time(0)));
    unsigned char r = rand() % 256;
    unsigned char g = rand() % 256;
    unsigned char b = rand() % 255;
    return Color{r, g, b, 255}; 
}

Color IncreaseColorBy(Color color, int increaseAmount) {
    unsigned char num = increaseAmount;
    color.r = (color.r + num > 255) ? 255 : color.r + num;
    color.g = (color.g + num > 255) ? 255 : color.g + num;
    color.b = (color.b + num > 255) ? 255 : color.b + num;
    return color;
}

void drawLinearInterprolation(Vector2 p1, Vector2 p2){
    //float pointY;
    for (float i = 0; i < 1; i += 0.01f)
    {
        float x = p1.x + i * (p2.x - p1.x); //Interpolation Formula
        float y = p1.y + i * (p2.y - p1.y); //redundancy found, formular similar to the one in maths.cpp
        
        DrawPixel((int)x, (int)y, RED);
    }
}

void drawBezier(){
    Vector2 point = {0,0};
    Vector2 previousPoint = {balls[0].pos.x, balls[0].pos.y};
    
    for (float t = 0; t < 1.0f + drawingRefreshRate; t += drawingRefreshRate){
        //point = bernstein(balls, ballCount, t);
        point = deCasteljau(t);
        DrawLineEx(previousPoint, point, 5, RED); 
        previousPoint = point;
    }
}

void drawExistingBalls(){
    for (int i = 0; i < ballNum; i++)
    {
        DrawText(TextFormat("X: %i, Y: %i",(int)balls[i].pos.x, (int)balls[i].pos.y), balls[i].pos.x - 30, balls[i].pos.y - 20,5, RED);
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
        if(i > 0){
            //drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            //DrawLineEx(balls[i-1].pos, balls[i].pos, 1, GRAY);
            drawLinearInterprolation(balls[i-1].pos, balls[i].pos);
            drawBezier();
        }
    }
}

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