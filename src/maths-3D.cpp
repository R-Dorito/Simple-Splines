#include "raylib.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"
#include "../headers/globals.h"

#include <iostream>
#include <cmath> 

float cox_de_boor(int i, int degreeOfSpline, float t, double knots[]) {

   //from Wiki B_{i,p}(x):={\frac {x-t_{i}}{t_{i+p}-t_{i}}}B_{i,p-1}(x)+{\frac {t_{i+p+1}-x}{t_{i+p+1}-t_{i+1}}}B_{i+1,p-1}(x).
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

