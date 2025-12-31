#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"
#include "../headers/globals.h"

#include <iostream>
#include <cmath> 

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

Vector2 bernstein(float t){
    float resultX = 0.0f;
    float resultY = 0.0f;
    int nt = ballNum-1;

    for(int i = 0; i < ballNum; i++){
        resultX += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.x;
        resultY += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.y;
        //DrawLine(balls[i].pos.x, balls[i].pos.y, resultX, resultY, PINK);
    }
    return {resultX, resultY};
}

Vector2 deCasteljau(float t){

    Vector2 Q[ballNum];
    Vector2 oldPoint;

    // I dont want to edit the balls array
    for (int i = 0; i < ballNum; i++) {
        Q[i] = balls[i].pos; 
    } 

    for(int i = 0; i < ballNum - 1; i++){ 
        // dont forget to check the "- 1", if the point starts at 0,0 or it's flying off somewhere, it's likely a -1 problem
        for(int j = 0; j < ballNum - i - 1; j++){ 
            oldPoint = Q[j];
            Q[j].x = (Q[j].x * (1-t)) + (Q[j+1].x * t);
            Q[j].y = (Q[j].y * (1-t)) + (Q[j+1].y * t);
            //DrawLineEx(oldPoint, Q[j+1], 2, c);
        }
    }

    return Q[0]; // this is the single point location after reducing all the balls on the 
}

float cox_de_boor(int i, int degreeOfSpline, float t, double knots[]) {
    double left = 0.0;
    double right = 0.0;

    if (degreeOfSpline == 0) {
        if(knots[i] <= t && t < knots[i + 1]) {
            return 1.0;
        }
        else{
            return 0.0;
        }
    } 

    if (knots[i + degreeOfSpline] != knots[i]) {
        left = (t - knots[i]) / (knots[i + degreeOfSpline] - knots[i]);
    }

    if (knots[i + degreeOfSpline + 1] != knots[i + 1]) {
        right = (knots[i + degreeOfSpline + 1] - t) / (knots[i + degreeOfSpline + 1] - knots[i + 1]);
    }

    double leftPart = left * cox_de_boor(i, degreeOfSpline - 1, t, knots);
    double rightPart = right * cox_de_boor(i + 1, degreeOfSpline - 1, t, knots);

    return leftPart + rightPart;
}

Vector2 cox_de_boor_to_vectors(float t, int degreeOfSpline, double knots[]) {
    float x = 0.0f, y = 0.0f;
    for (int i = 0; i < ballNum; i++) {
        // Compute the B-spline basis function N_{i,k}(t) for each control point
        float N = cox_de_boor(i, degreeOfSpline, t, knots);
        x += N * balls[i].pos.x;
        y += N * balls[i].pos.y;
    }
    return {x, y};
}