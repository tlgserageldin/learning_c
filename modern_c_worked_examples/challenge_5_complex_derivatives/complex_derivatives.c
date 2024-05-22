/* Can you extend the derivative (challenge 2) to the complex domain: that is, functions that receive and return double complex values?
   z = z0 + h = (x0 + h) + i*y0
   F(z) = u(x, y) + i*v(x, y)
   f(z) = (F(x0 + h + i*y0) - F(x0 + i*y0)) / h
   as h -> 0 */
#include <tgmath.h>
#include <stdlib.h>
#include <stdio.h>

/* numerical derivative of function F */
double f(double x);
/* original function which to derivate */
double F(double x);

/* for complex function F(z) = u(x, y) + i*v(x, y)*/
double u(double x, double y);
double v(double x, double y);
/* approx of derivative of function F */
double complex cF(double real, double complex imag);

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
  /* will use the symmetrical difference quotient
     f(x+h) - f(x-h) / 2h */
  double h = 0.001; // if good enough for ti good enough for me
  return (F(x+h)-F(x-h))/(2*h);
}

double u(double x, double y) {
}

