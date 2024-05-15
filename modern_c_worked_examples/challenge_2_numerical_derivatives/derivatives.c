/*
Something we’ll deal with a lot is the concept of numerical algorithms.
To get your handsdirty,see if you can implement the numerical derivative double f(double x) of a function double F(double x).
Implement this with an example F for the function that you use for this exercise.
A good primary choice for F would be a function for which you know the derivative, such as sin, cos, or sqrt.
This allows you to check your results for correctness.
*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// numerical derivative of function F
double f(double x);
// original function which to derivate
double F(double x);

int main(int argc, char* argv[argc+1]) {
    double result = f(2);
    printf("expented result: %f", 0.354);
    printf("result: %f", result);
    return EXIT_SUCCESS;
}

double F(double x) {
    return sqrtf(x);
}

double f(double x) {
    // will use the symmetrical difference quotient
    // f(x+h) - f(x-h) / 2h
    double h = 0.001; // if good enough for ti good enough for me
    return (F(x+h)-F(x-h))/(2*h);
}
