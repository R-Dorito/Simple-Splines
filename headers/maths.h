#include "../headers/balls.h"
#include "raylib.h" 

#ifndef MATHS_H
#define MATHS_H

extern Ball balls[]; 
extern int ballNum;  
extern float startBallRadius;

float factorio(int number);
float binomials(int number, int k_Value);
Vector2 bernstein(float t);
Vector2 deCasteljau(float t);

//float cox_de_boor(int itteration, int degree_of_spline, double ticker, double knots[]);
Vector2 findSpline(float t, int n, int degree_of_spline, Ball balls[], double knots[]);


#endif