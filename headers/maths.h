#include "raylib.h" 
#include "globals.h"

#ifndef MATHS_H
#define MATHS_H

float factorio(int number);
float binomials(int number, int k_Value);
Vector2 bernstein(float t);
Vector2 deCasteljau(float t);
Vector2 interpolated_deCasteljau(float t);

//float cox_de_boor(int itteration, int degree_of_spline, double ticker, double knots[]);
Vector2 cox_de_boor_to_vectors(float t, int degree_of_spline, double knots[]);


#endif