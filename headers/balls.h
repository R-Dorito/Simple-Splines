#include "raylib.h"

#ifndef BALLS_H
#define BALLS_H

typedef struct  Ball {
    Vector2 pos;
    float radius;
    Color colour;
} Ball;

#endif