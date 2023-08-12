/* Can you compare the time efficiency of your sorting programs (challenge 1) with data sizes of several orders of magnitude?
   Be careful to check that you have some randomness in the creation of the data and that the data size does not exceed the available memory of your computer.
   For both algorithms, you should roughly observe a behavior that is proportional to N logN, where N is the number of elements that are sorted. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N1 10
#define N2 100
#define N3 500
#define N4 1000
#define N5 10000

void print_array(size_t len, uint32_t array[]) {
    for (size_t i = 0; i < len; ++i) {
        printf("[%zu]: %u\n", i, array[i]);
    }
    printf("\n");
}

void copy_array(size_t n, uint32_t src[n], uint32_t dst[n]) {
    for (size_t i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
}

int test_sort(size_t n, uint32_t array[n]) {
    for (size_t i = 1; i < n-1; i++) {
        if (array[i] < array[i-1]) {
            return 0;
        }
    }
    return 1;
}

void my_mergesort(size_t n, uint32_t array[n]) {
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
    uint32_t left[left_e];
    uint32_t right[right_e];
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

void my_q_sort(size_t len, uint32_t array[]) {
    if (len < 2) {
        return;
    } else {
        uint32_t smaller[len];
        uint32_t larger[len];
        size_t smaller_e = 0, larger_e = 0;
        uint32_t pivot = array[0];
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

int main(void) {
    struct timespec start;
    struct timespec end;
    uint32_t arr1[N1], arr1_copy[N1];
    for (size_t i = 0; i < N1; ++i) {
        arr1[i] = arc4random();
    }
    copy_array(N1, arr1, arr1_copy);
    uint32_t arr2[N2], arr2_copy[N2];
    for (size_t i = 0; i < N2; ++i) {
        arr2[i] = arc4random();
    }
    copy_array(N1, arr2, arr2_copy);
    uint32_t arr3[N3], arr3_copy[N3];
    for (size_t i = 0; i < N3; ++i) {
        arr3[i] = arc4random();
    }
    copy_array(N1, arr3, arr3_copy);
    uint32_t arr4[N4], arr4_copy[N4];
    for (size_t i = 0; i < N4; ++i) {
        arr4[i] = arc4random();
    }
    copy_array(N1, arr4, arr4_copy);
    uint32_t arr5[N5], arr5_copy[N5];
    for (size_t i = 0; i < N5; ++i) {
        arr5[i] = arc4random();
    }
    copy_array(N1, arr5, arr5_copy);

    timespec_get(&start, TIME_UTC);
    my_q_sort(N1, arr1);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, qsort took %ld nanoseconds\n", N1, (end.tv_nsec-start.tv_nsec));

    timespec_get(&start, TIME_UTC);
    my_mergesort(N1, arr1_copy);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, mergesort took %ld nanoseconds\n", N1, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_q_sort(N2, arr2);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, qsort took %ld nanoseconds\n", N2, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_mergesort(N2, arr2_copy);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, mergesort took %ld nanoseconds\n", N2, end.tv_nsec-start.tv_nsec);
    
    timespec_get(&start, TIME_UTC);
    my_q_sort(N3, arr3);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, qsort took %ld nanoseconds\n", N3, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_mergesort(N3, arr3_copy);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, mergesort took %ld nanoseconds\n", N3, end.tv_nsec-start.tv_nsec);
    
    timespec_get(&start, TIME_UTC);
    my_q_sort(N4, arr4);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, qsort took %ld nanoseconds\n", N4, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_mergesort(N4, arr4_copy);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, mergesort took %ld nanoseconds\n", N4, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_q_sort(N5, arr5);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, qsort took %ld nanoseconds\n", N5, end.tv_nsec-start.tv_nsec);

    timespec_get(&start, TIME_UTC);
    my_mergesort(N5, arr5_copy);
    timespec_get(&end, TIME_UTC);
    printf("For an array of uint32 of size %d, mergesort took %ld nanoseconds\n", N5, end.tv_nsec-start.tv_nsec);

    return 0;
}
