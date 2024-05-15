/*
Can you do
    1 A merge sort (with recursion)
    2 A quick sort (with recursion)
on arrays with sort keys such as double or strings to your liking?

Can you provide a simple test routine.
*/
#include <stdlib.h>
#include <float.h>
#include <assert.h>

// returns 0 or 1 if the double array of n_elems is sorted
size_t is_double_array_sorted(size_t n_elems, double const array[n_elems]);

int main(int argc, char* argv[argc+1]) {
    return EXIT_SUCCESS;
}

// checks a double array of n_elems length for ascending order
size_t is_double_array_sorted(size_t n_elems, double const array[n_elems]) {
    double prev = array[0];
    for (size_t i = 1; i < n_elems; i++) {
        if (array[i] < prev) {
            return EXIT_FAILURE;
        }
        prev = array[i];
    }
    return EXIT_SUCCESS;
}
