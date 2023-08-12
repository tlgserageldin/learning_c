/*vim:foldmethod=marker*/
#include <assert.h>
#include <float.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(size_t len, double array[]) {
    for (size_t i = 0; i < len; ++i) {
        printf("[%zu]: %g\n", i, array[i]);
    }
    printf("\n");
}

void copy_array(size_t n, double src[n], double dst[n]) {
    for (size_t i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
}

int test_sort(size_t n, double array[n]) {
    for (size_t i = 1; i < n-1; i++) {
        if (array[i] < array[i-1]) {
            return 0;
        }
    }
    return 1;
}

/* mergesort for doubles */
void my_mergesort(size_t n, double array[n]) {
    if (n == 1) {
        return;
    }
    size_t left_e, right_e;
    if (n % 2) {
        left_e = n/2+1;
        right_e = n/2;
    } else {
        left_e = right_e = n/2;
    }
    assert(left_e + right_e == n);
    double left[left_e];
    double right[right_e];
    for (size_t i = 0, li = 0, ri = 0; i < n; ++i) {
        if (li < left_e) {
            left[li] = array[i];
            ++li;
        } else {
            right[ri] = array[i];
            ++ri;
        }
    }
    my_mergesort(left_e, left);
    my_mergesort(right_e, right);
    for (size_t i = 0, li = 0, ri = 0; i < n; ++i) {
        if (li == left_e) {
            while (ri != right_e) {
                array[i] = right[ri];
                ++ri; ++i;
            }
            break;
        } else if (ri == right_e) {
            while (li != left_e) {
                array[i] = left[li];
                ++li; ++i;
            }
            break;
        } else {
            if (left[li] <= right[ri]) {
                array[i] = left[li];
                ++li;
            } else {
                array[i] = right[ri];
                ++ri;
            }
        }
    }
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
} //

// this uses pointers, should rewrite using only arrays...
// also this doesnt handle lists of two or less
void my_q_sort_old(double* array, size_t len) {
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
}

/*int main(void) {
    double arr1[N] = {2.5, 99.4, 72.5, 100, 86.6, 11, 90.9, 17.17, 878, 1};
    double arr2[2] = {2.3, 2.1};
//    my_q_sort(N, arr1);
//    my_q_sort(N2, arr2);
//    assert(test_sort(arr1, 10));
    my_mergesort(N, arr1);
    assert(test_sort(N, arr1));
    my_mergesort(N2, arr2);
    assert(test_sort(N2, arr2));
    return 0;
}*/





