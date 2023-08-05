/*vim:foldmethod=marker*/
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define N2 2

void print_array(size_t len, double array[]) {
    for (size_t i = 0; i < len; ++i) {
        printf("[%zu]: %g\n", i, array[i]);
    }
    printf("\n");
}

/*
divide the unsorted array into subarrays until size one
then compare the elements of each array, combinging based on size until back to original len
*/
void my_merge_sort(size_t len, double array[]) {
}

// rewriting q_sort using arrays only
// much shorter too, im getting better LFG
void my_q_sort(size_t len, double array[]) {
    if (len < 2) {
        return;
    } else {
        double smaller[len];
        double larger[len];
        size_t smaller_e = 0, larger_e = 0;
        double pivot = array[0];
        for (size_t i = 1; i < len; ++i) {
            if (array[i] <= pivot) {
                smaller[smaller_e] = array[i];
                ++smaller_e;
            } else {
                larger[larger_e] = array[i];
                ++larger_e;
            }
        }
        my_q_sort(smaller_e, smaller);
        my_q_sort(larger_e, larger);
        size_t elem = 0;
        for (size_t i = 0; i < smaller_e; ++i) {
            array[elem] = smaller[i];
            ++elem;
        }
        array[elem] = pivot;
        ++elem;
        for (size_t i = 0; i < larger_e; ++i) {
            array[elem] = larger[i];
            ++elem;
        }
    }
}

// this uses pointers, should rewrite using only arrays...
// also this doesnt handle lists of two or less
void my_q_sort_old(double* array, size_t len) {/*{{{*/
    if (len > 2) {
        size_t si, bi;
        si = bi = 0;
        double smallarr[len-1];
        double bigarr[len-1];
        double* pivot = (array);
        for (size_t i = 1; i < len; i++) {
            // divide into a left array
            if (*(array+i) <= *pivot) {
                smallarr[si] = *(array+i);
                si++;
            } else {
                // and right array
                bigarr[bi] = *(array+i);
                bi++;
            }
        }
        assert(si+bi==len-1);
        // sort the two arrays
        my_q_sort_old(smallarr, si);
        my_q_sort_old(bigarr, bi);
        // combine the smallerarr + pivot + biggerarr
        double retarr[len];
        size_t reti = 0;
        for (size_t i = 0; i < si; i++) {
            retarr[reti] = *(smallarr+i);
            reti++;
        }
        retarr[reti] = *pivot;
        reti++;
        for (size_t i = 0; i < bi; i++) {
            retarr[reti] = *(bigarr+i);
            reti++;
        }
        assert(reti == len);
        for (size_t i = 0; i < len; i++) {
            *(array+i) = retarr[i];
        }
    }
}/*}}}*/

int test_sort(double* array, size_t len) {/*{{{*/
    for (size_t i = 0; i < len-1; i++) {
        if (*(array+i) > *(array+i+1)) {
            return 0;
        }
    }
    return 1;
}/*}}}*/

int main(void) {
    double arr1[N] = {2.5, 99.4, 72.5, 100, 86.6, 11, 90.9, 17.17, 878, 1};
    double arr2[2] = {2.3, 2.1};
    my_q_sort(N, arr1);
    my_q_sort(N2, arr2);
//    assert(test_sort(arr1, 10));
    print_array(N, arr1);
    print_array(N2, arr2);
    return 0;
}





