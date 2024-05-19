/*
calculate pi to n decimals
4 * arctan(1) = pi
arctan(1) = sum from n=0 to inf of -1^n / (2n+1)

about 1.4 decimals per iteration
pi = 16*atan(1/5) - 4*atan(1/239)
atan(1/5) sum from n=0 to inf of -(1/5)^n / (2n+1)
atan(1/239) som from n=0 to inf of 

long double has 33 digits in 64 bit
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define ITER_LIMIT 999

/*pi = 16 * atan(1/5) - 4 * atain(1/239)
  grows at about 1.4 decimals per iteration
  atan(x) = -1^n * x^(2n+1) / (2n+1)
  double had precision of 14 decimal places*/
double pi_to_n_digits(size_t n);

int main(int argc, char* argv[argc+1]) {
    printf("precision: %d value: %.16f\n", 4, pi_to_n_digits(4));
    printf("precision: %d value: %.16f\n", 8, pi_to_n_digits(8));
    printf("precision: %d value: %.16f\n", 12, pi_to_n_digits(12));
    return EXIT_SUCCESS;
}

double pi_to_n_digits(size_t n) {
    double total = 0;
    double atan5 = 0;
    double atan239 = 0;
    for (size_t iterations = 0; iterations <= n; iterations++) {
        atan5 = pow(-1.0,iterations) * pow(1.0/5.0, 2*iterations+1) / (2*iterations+1);
        atan239 = pow(-1.0,iterations) * pow(1.0/239.0, 2*iterations+1) / (2*iterations+1);
        total += 16.0 * atan5 - 4 * atan239;
    }
    return total;
}
