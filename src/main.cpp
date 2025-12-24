#include "raylib.h"
#include <iostream>
#include <cmath> 

#define MAX_BALLS 5000

const int screenWidth = 800;
const int screenHeight = 600;

typedef struct  Ball {
    Vector2 pos;
    float radius;
    Color colour;
} Ball;

Ball balls[MAX_BALLS]; 
int ballNum = 0;    
float startBallRadius = 10;

float factorio(int number){
    if (number == 0){return 1;}
    return number * factorio(number - 1);
}

float binomials(int number, int k_Value){
    //std::cout << "binomials hit" << std::endl;
    if (k_Value > number)
        return 0;
  
  	// base condition when k and n are equal or k = 0
    if (k_Value == 0 || k_Value == number)
        return 1;
    return factorio(number) / (factorio(k_Value) * factorio(number-k_Value));
}

void drawLinearInterprolation(Vector2 p1, Vector2 p2){
    //float pointY;
    for (float i = 0; i < 1; i += 0.01f)
    {
        float x = p1.x + i * (p2.x - p1.x); //Interpolation Formula
        float y = p1.y + i * (p2.y - p1.y);
        
        DrawPixel((int)x, (int)y, RED);
    }
}

Vector2 bernstein(float t){
    float resultX = 0.0f;
    float resultY = 0.0f;
    int nt = ballNum-1;

    for(int i = 0; i < ballNum; i++){
        resultX += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.x;
        resultY += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.y;
    }
    return {resultX, resultY};
}

float homeMadeLarp (float val1, float val2, float t){
    return val1 * (1-t) + val2 * t;
}

Vector2 deCasteljau(float t){

    Vector2 Q[ballNum];

    for (int i = 0; i < ballNum; i++) {
        Q[i] = balls[i].pos; // P for point.
    } 

    for(int i = 0; i < ballNum - 1; i++){ 
        // dont forget to check the "- 1", if the point starts at 0,0 or it's flying off somewhere, it's likely a -1 problem
        for(int j = 0; j < ballNum - i - 1; j++){ 
            // reduce the number of itterations for each step. So reduce "i" over time
            Q[j].x = (Q[j].x * (1-t)) + (Q[j+1].x * t);
            Q[j].y = (Q[j].y * (1-t)) + (Q[j+1].y * t);
        }
    }

    return {Q[0]}; // this is the single point location after reducing all the balls on the 
}

void drawBezier(){
    Vector2 point = {0,0};
    Vector2 previousPoint = {balls[0].pos.x, balls[0].pos.y};
    
    for (float t = 0; t < 1.0f; t += 0.01f){
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



int main(void)
{
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
            drawExistingBalls();

            //below is the current ball location
            DrawCircleV(ballPosition, startBallRadius, LIME);
            DrawText(TextFormat("X: %.0f, Y: %.0f",ballPosition.x, ballPosition.y), 0,0,5, BLACK);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
