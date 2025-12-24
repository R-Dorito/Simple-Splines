#include "../headers/balls.h"
#include "raylib.h" 

#ifndef MATHS_H
#define MATHS_H

float factorio(int number);
float binomials(int number, int k_Value);
// void drawLinearInterprolation(Vector2 p1, Vector2 p2);
Vector2 bernstein(Ball balls[], int n, float t);
Vector2 deCasteljau(Ball balls[], int n, float t);
// void drawBezier(Ball balls[], int n);
// void drawExistingBalls(Ball balls[], int n);

#endif