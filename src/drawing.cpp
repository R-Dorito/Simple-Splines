#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"

#include <stdlib.h>   
#include <iostream>
#include <cmath> 
#include <ctime> 

float drawingRefreshRate = 0.01f;

Color getNewColour(){
    srand(static_cast<unsigned int>(time(0)));
    unsigned char r = rand() % 256;
    unsigned char g = rand() % 256;
    unsigned char b = rand() % 255;
    return Color{r, g, b, 10}; 
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

void drawSpline_deBoor(int lineThickness, Color c){
    int degreeOfSpline = (numMin(ballNum - 1, 3));
    //double knots[] = {0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 3.0, 3.0}; // CAN ONLY Take in a few control points
    Vector2 point, previousPoint;
    int totalKNots = degreeOfSpline + ballNum + 1; // test numbers as theres only 4 of them

    double calculatedKnots[totalKNots];

    for (int i = 0; i <= degreeOfSpline; ++i) {
        calculatedKnots[i] = 0.0;
    }

    // Set the last (degree_of_spline + 1) knots to 1
    for (int i = ballNum; i < totalKNots; ++i) {
        calculatedKnots[i] = 1.0;
    }

    // Set the intermediate knots to be evenly spaced between 0 and 1
    for (int i = degreeOfSpline + 1; i < ballNum; ++i) {
        calculatedKnots[i] = (double)(i - degreeOfSpline) / (ballNum - degreeOfSpline);
    }

    //knots = calculatedKnots;

    Vector2 startingPoint = {balls[0].pos.x, balls[0].pos.y};
    previousPoint = startingPoint;

    float t = calculatedKnots[degreeOfSpline];
    while (t <= calculatedKnots[ballNum]) {

        double t_clamped = t > calculatedKnots[ballNum] ? calculatedKnots[ballNum] : t;
        point = findSpline(t_clamped, ballNum, degreeOfSpline, balls, calculatedKnots);
        //point.x += startingPoint.x;
        //point.y += startingPoint.y;
        std::cout << "point.x " << point.x << " point. y " << std::endl;
        DrawLineEx(previousPoint, point, lineThickness, c); 
        previousPoint = point;

        t += drawingRefreshRate;
    }
    
    // for (float t = calculatedKnots[degreeOfSpline]; t <= calculatedKnots[ballNum]; t += drawingRefreshRate) {
    //     point = findSpline(t, ballNum, degreeOfSpline, balls, calculatedKnots);
    //     //point.x += startingPoint.x;
    //     //point.y += startingPoint.y;
    //     std::cout << "point.x " << point.x << " point. y " << std::endl;
    //     DrawLineEx(previousPoint, point, 5, RED); 
    //     previousPoint = point;
    // }
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
            
            drawBezier(3, ORANGE);
            drawSpline_deBoor(2, DARKBLUE);
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

Ball* getNewBallPosition(Vector2 mouseLocation){
    for (int i = 0; i < ballNum; i++) {
        // Calculate the distance between the mouse and the circle's center
        float distance = sqrt(pow(mouseLocation.x - balls[i].pos.x, 2) + pow(mouseLocation.y - balls[i].pos.y, 2));

        // If the distance is less than or equal to the circle's radius, the mouse is over the circle
        if (distance <= startBallRadius) {
            std::cout << "ball over" << std::endl;
            return &balls[i];
        }
    }
    return nullptr;
}