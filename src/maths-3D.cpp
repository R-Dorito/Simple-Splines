#include "raylib.h"
#include "../headers/balls.h"
#include "../headers/drawing.h"
#include "../headers/globals.h"
#include "../headers/maths-2D.h"

#include <iostream>
#include <cmath> 

Vector3 cox_de_boor_3D(float t, int degreeOfSpline, double knots[]) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    for (int i = 0; i < ballNum; i++) {
        // Compute the B-spline basis function N_{i,k}(t) for each control point
        float N = cox_de_boor(i, degreeOfSpline, t, knots);
        x += N * balls_3d[i].pos.x;
        y += N * balls_3d[i].pos.y;
        z += N * balls_3d[i].pos.z;
    }
    return {x, y, z};
}

