#include "../headers/balls.h"
#include "raylib.h" 

#ifndef MATHS_H
#define MATHS_H

void drawLinearInterprolation(Vector2 p1, Vector2 p2);
void drawBezier(Ball balls[], int n);
void drawExistingBalls(Ball balls[], int n);

#endif