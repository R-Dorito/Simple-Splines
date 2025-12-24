#include "raylib.h"
#include "../headers/maths.h"
#include "../headers/balls.h"

#include <iostream>
#include <cmath> 

float factorio(int number){
    if (number == 0){return 1;}
    return number * factorio(number - 1);
}

float binomials(int number, int k_Value){
    //std::cout << "binomials hit" << std::endl;
    if (k_Value > number)
        return 0;
  
  	// base condition when k and n are equal or k = 0
    if (k_Value == 0 || k_Value == number)
        return 1;
    return factorio(number) / (factorio(k_Value) * factorio(number-k_Value));
}

Vector2 bernstein(Ball balls[], int n, float t){
    float resultX = 0.0f;
    float resultY = 0.0f;
    int nt = n-1;

    for(int i = 0; i < n; i++){
        resultX += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.x;
        resultY += binomials(nt,i) * pow(t,i) * pow((1-t),(nt-i)) * balls[i].pos.y;
    }
    return {resultX, resultY};
}

// float homeMadeLarp (float val1, float val2, float t){
//     return val1 * (1-t) + val2 * t;
// }

Vector2 deCasteljau(Ball balls[], int n, float t){

    Vector2 Q[n];

    for (int i = 0; i < n; i++) {
        Q[i] = balls[i].pos; // P for point.
    } 

    for(int i = 0; i < n - 1; i++){ 
        // dont forget to check the "- 1", if the point starts at 0,0 or it's flying off somewhere, it's likely a -1 problem
        for(int j = 0; j < n - i - 1; j++){ 
            // reduce the number of itterations for each step. So reduce "i" over time
            Q[j].x = (Q[j].x * (1-t)) + (Q[j+1].x * t);
            Q[j].y = (Q[j].y * (1-t)) + (Q[j+1].y * t);
        }
    }

    return Q[0]; // this is the single point location after reducing all the balls on the 
}

