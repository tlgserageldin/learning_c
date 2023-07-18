#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void my_q_sort(double* array, size_t len);
int test_sort(double* array, size_t len);

int main(void) {
	double arr1[10] = {2.5, 99.4, 72.5, 100, 86.6, 11, 90.9, 17.17, 878, 1};
	my_q_sort(arr1, 10);
	assert(test_sort(arr1, 10));
	for (size_t i = 0; i < 10; i++) {
		printf("%zu: %f\n", i, *(arr1+i));
	}
	return 0;
}

void my_q_sort(double* array, size_t len) {
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
		my_q_sort(smallarr, si);
		my_q_sort(bigarr, bi);
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

int test_sort(double* array, size_t len) {
	for (size_t i = 0; i < len-1; i++) {
		if (*(array+i) > *(array+i+1)) {
			return 0;
		}
	}
	return 1;
}

