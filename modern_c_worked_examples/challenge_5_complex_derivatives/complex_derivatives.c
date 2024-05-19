/*Can you extend the derivative (challenge 2) to the complex domain: that is, functions that receive and return double complex values?*/
#include <stdlib.h>
#include <tgmath.h>

// numerical derivative of function F
double complex f(double complex x);
// original function which to derivate
double complex F(double complex x);

int main(int argc, char* argv[argc+1]) {
    return EXIT_SUCCESS;
}

double complex F(double complex x) {
    return sqrt(x);
}

double complex f(double complex x) {
    double complex h = .001 + I;
    return (F(x+h) - F(x-h)) / (2*h);
}
