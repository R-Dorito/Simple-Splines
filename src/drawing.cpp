#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"
#include "../headers/globals.h"

#include <stdlib.h>   
#include <iostream>
#include <cmath> 
#include <ctime> 

float drawingRefreshRate = 0.01f;

void drawGuideLines(Vector2 p1, Vector2 p2){
    //float pointY;
    for (float i = 0; i < 1; i += 0.01f)
    {
        float x = p1.x + i * (p2.x - p1.x); //Interpolation Formula
        float y = p1.y + i * (p2.y - p1.y); //redundancy found, formular similar to the one in maths.cpp
        DrawPixel((int)x, (int)y, RED);
    }
}

void drawBezier(int lineThickness, Color c){
    Vector2 point = {0,0};
    Vector2 previousPoint = {balls[0].pos.x, balls[0].pos.y};
    
    for (float t = 0; t < 1.0f; t += drawingRefreshRate){

        point = deCasteljau(t);

        DrawLineEx(previousPoint, point, lineThickness, c); 
        previousPoint = point;
    }
}

int numMin(int numA, int numB) {
    return numA < numB ? numA : numB;
}

int numMax(int numA, int numB) {
    return numA > numB ? numA : numB;
}

void drawSpline_deBoor(int degree, int lineThickness, Color c){
    int degreeOfSpline = degree;//numMin(ballNum - 1, 3);
    //double knots[] = {0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 3.0, 3.0}; // CAN ONLY Take in a few control points
   
    Vector2 point, previousPoint;
    int totalKNots = degreeOfSpline + ballNum + 1;

    double calculatedKnots[totalKNots];

    for (int i = 0; i <= degreeOfSpline; ++i) {
        calculatedKnots[i] = 0.0;
    }

    for (int i = ballNum; i < totalKNots; ++i) {
        calculatedKnots[i] = 1.0;
    }

    for (int i = degreeOfSpline + 1; i < ballNum; ++i) {
        calculatedKnots[i] = (double)(i - degreeOfSpline) / (ballNum - degreeOfSpline);
    }

    Vector2 startingPoint = {balls[0].pos.x, balls[0].pos.y};
    previousPoint = startingPoint;

    float t = calculatedKnots[degreeOfSpline];

    // Draw knot locations on the spline
    for (int i = degreeOfSpline; i < ballNum; i++) {
        point = cox_de_boor_to_vectors(calculatedKnots[i], degreeOfSpline, calculatedKnots);
        DrawCircleV(point, 5.0f, PURPLE);
    }

    while (t <= calculatedKnots[ballNum]) {
        double t_clamped = t > calculatedKnots[ballNum] ? calculatedKnots[ballNum] : t;
        point = cox_de_boor_to_vectors(t_clamped, degreeOfSpline, calculatedKnots);
        DrawLineEx(previousPoint, point, lineThickness, c); 
        previousPoint = point;

        t += drawingRefreshRate;
    }
}

void drawExistingBalls(int degree, Vector2 mouseLocation){
    for (int i = 0; i < ballNum; i++)
    {
        DrawText(TextFormat("X: %i, Y: %i",(int)balls[i].pos.x, (int)balls[i].pos.y), balls[i].pos.x - 30, balls[i].pos.y - 20,5, RED);

        if(CheckCollisionPointCircle(mouseLocation, balls[i].pos, balls[i].radius)){
            DrawCircleLines(
                balls[i].pos.x,
                balls[i].pos.y,
                balls[i].radius + 2.0f,
                RED
            );
        }
        
        DrawCircleV(balls[i].pos, balls[i].radius, balls[i].colour);
        
        if(i > 0){
            //drawGuideLines(balls[i-1].pos, balls[i].pos);
            //DrawLineEx(balls[i-1].pos, balls[i].pos, 1, GRAY);
            drawGuideLines(balls[i-1].pos, balls[i].pos);
            
            drawBezier(3, ORANGE);
            drawSpline_deBoor(degree, 2, DARKBLUE);
        }



    }
}