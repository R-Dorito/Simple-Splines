#include "balls.h"
#include "maths.h"
#include "globals.h"
#include "raylib.h" 

#ifndef DRAWING_H
#define DRAWING_H

void drawGuideLines(Vector2 p1, Vector2 p2);
void drawBezier();
void drawExistingBalls(int degree, Vector2 mouseLocation);
#endif