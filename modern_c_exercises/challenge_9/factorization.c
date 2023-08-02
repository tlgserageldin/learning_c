/*
Now that we’ve covered functions, see if you can implement a program factor that receives a number N on the command line and prints out:
N: F0 F1 F2 ...
where F0 and so on are all the prime factors of N.
The core of your implementation should be a function that, given a value of type size_t, returns its smallest prime factor.
*/
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// for a given natural number, will return the smallest prime factor
size_t smallest_prime_factor(size_t N) {
    if (N == 1) {
        return 1;
    } else if (N % 2) {
        for (size_t i = 3; i < sqrt(N); i += 2) {
            if (!(N % i)) {
                return i;
            }
        }
        return N;
    } else {
        return 2;
    }
}

/*
retrieve N from argv
print N
while N != 1
    find smallest prime factor of N
    while !(N % spm)
        N / spm
    print spf
*/
int main(int argc, char* argv[argc+1]) {
    if (argc < 2) {
        printf("please enter a natural number to find the prime facorization...\n\n");
        return EXIT_FAILURE;
    } else if (argc > 2) {
        printf("please only enter one argument...\n\n");
        return EXIT_FAILURE;
    } else {
        char* num = argv[1];
        long N = strtol(num, NULL, 0);
        if (N < 0 || !N) {
            printf("please only enter natural numbers...");
            return EXIT_FAILURE;
        }
        printf("%ld: ", N);
        while (N != 1) {
            size_t spf = smallest_prime_factor(N);
            while (!(N % spf)) {
                N = N / spf;
            }
            printf("%zu ", spf);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
