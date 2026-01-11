#include "raylib.h"

#ifndef BALLS_H
#define BALLS_H

typedef struct  Ball {
    Vector2 pos;
    float radius;
    Color colour;
} Ball;

typedef struct  Ball_3D {
    Vector3 pos;
    float radius;
    Color colour;
} Ball_3D;

#endif