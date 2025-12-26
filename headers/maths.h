#include "../headers/balls.h"
#include "raylib.h" 

#ifndef MATHS_H
#define MATHS_H

extern Ball balls[]; 
extern int ballNum;  

float factorio(int number);
float binomials(int number, int k_Value);
Vector2 bernstein(float t);
Vector2 deCasteljau(float t);

#endif