/*
Something we’ll deal with a lot is the concept of numerical algorithms.
To get your hands dirty, see if you can implement the numerical derivative double f(double x) of a function double F(double x).
Implement this with an example F for the function that you use for this exercise.
A good primary choice for F would be a function for which you know the derivative, such as sin, cos, or sqrt.
This allows to check your results for correctness.
*/
#include <math.h>
#include <stdio.h>
#include <tgmath.h>

double deriv(double x, double f(double));

int main(void) {
	double res = deriv(3.14159, sin);
	double res2 = deriv(0, sin);
	double res3 = deriv(3.14159/2, sin);
	//printf("sin of 3.14/2 should be 1, it is: %f\n", testres);
	printf("derive of sin at pi should be ~-1, fn returns: %f\n", res);
	printf("derive of sin at 0 should be ~1, fn returns: %f\n", res2);
	printf("derive of sin at pi/2 should be ~0, fn returns: %f\n", res3);
	return 0;
}

double deriv(double x, double (*f)(double)) {
	double h = 0.00001;
	return ((f(x+h) - f(x))/h);
}
