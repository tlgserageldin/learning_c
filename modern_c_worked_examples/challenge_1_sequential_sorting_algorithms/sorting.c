/*
Can you do
    1 A merge sort (with recursion)
    2 A quick sort (with recursion)
on arrays with sort keys such as double or strings to your liking?

Can you provide a simple test routine.
*/
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <assert.h>

// returns 0 or 1 if the double array of n elems is sorted
size_t is_double_array_sorted(size_t const n, double const array[n]);
// print double array of n elements
void print_double_array(size_t const n, double const array[n]);
// in-place merge sort of a double array of n elements
void merge_sort_double(size_t const n, double array[n]);
// in-place quick sort of a double array of n elements, range of [DBL_MIN, DBL_MAX)
void quick_sort_double(size_t const n, double array[n]);

int main(int argc, char* argv[argc+1]) {
    double test_array[] = { 1.0, 0.0, 2.4, 2.3 };
    double test_array_1[] = { 0.0, 1.0, 0.0, 2.4, 2.3 };
    quick_sort_double(5, test_array_1);
    print_double_array(5, test_array_1);
    return EXIT_SUCCESS;
}

size_t is_double_array_sorted(size_t const n, double const array[n]) {
    double prev = array[0];
    for (size_t i = 1; i < n; i++) {
        if (array[i] < prev) {
            return EXIT_FAILURE;
        }
        prev = array[i];
    }
    return EXIT_SUCCESS;
}

void print_double_array(size_t const n, double const array[n]) {
    for (size_t i = 0; i < n; i++) {
        printf("array[%zu] = %f\n", i, array[i]);
    }
}

void merge_sort_double(size_t const n, double array[n]) {
    // base case
    if (n == 1) {
        return;
    }
    // create the two smaller arrays to recursively call from
    size_t l_array_e;
    size_t r_array_e;
    if (n % 2) {
        l_array_e = n/2;
        r_array_e = n/2+1;
    } else {
        l_array_e = r_array_e = n/2;
    }
    double l_array[l_array_e];
    double r_array[r_array_e];
    // populate the arrays
    for (size_t i = 0; i < l_array_e; i++) {
        l_array[i] = array[i];
    }
    for (size_t i = 0; i < r_array_e; i++) {
        r_array[i] = array[i+l_array_e];
    }
    // recursive call
    merge_sort_double(l_array_e, l_array);
    merge_sort_double(r_array_e, r_array);
    // reconstruct array
    size_t l_idx = 0;
    size_t r_idx = 0;
    for (size_t i = 0; i < n; i++) {
        if (l_idx == l_array_e) { // if l_array is exhausted
            array[i] = r_array[r_idx];
            r_idx++;
        } else if (r_idx == r_array_e) { // if r_array is exhausted
            array[i] = l_array[l_idx];
            l_idx++;
        } else if (l_array[l_idx] <= r_array[r_idx]) { // if l_array elem is smaller than the r_array elem
            array[i] = l_array[l_idx];
            l_idx++;
        } else {
            array[i] = r_array[r_idx];
            r_idx++;
        }
    }
}

void quick_sort_double(size_t const n, double array[n]) {
    // base case
    if (n == 1 || n == 0) {
        return;
    }
    // assign pivot and create l and r array
    double pivot = array[0];
    size_t l_count = 0;
    size_t r_count = 0;
    double l_arr[n-1];
    double r_arr[n-1];
    // assign empty = DBL_MAX
    // TODO: maybe dont need
    for (size_t i = 0; i < n-1; i++) {
        l_arr[i] = r_arr[i] = DBL_MAX;
    }
    // populate arrays
    for (size_t i = 1; i < n; i++) {
        if (array[i] <= pivot) {
            l_arr[l_count] = array[i];
            l_count++;
        } else {
            r_arr[r_count] = array[i];
            r_count++;
        }
    }
    // recursive call
    // only iterate through the elements that are populated
    quick_sort_double(l_count, l_arr);
    quick_sort_double(r_count, r_arr);
    // rebuild array
    // put the sorted l array
    for (size_t i = 0; i < l_count; i++) {
        array[i] = l_arr[i];
    }
    array[l_count] = pivot;
    for (size_t i = 0; i < r_count; i++) {
        array[l_count+1+i] = r_arr[i];
    }
}
