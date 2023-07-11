#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

long calc_smallest_side_area(const long l, const long w, const long h) {
	if (l >= w && l >= h) {
		return w*h;
	}
	else if (w >= l && w >= h) {
		return l*h;
	}
	else {
		return w*l;
	}
}

long calc_surface_area(const long l, const long w, const long h) {
	return (2*l*w) + (2*l*h) + (2*w*h);
}

long calc_wrapping_ribbon(const long l, const long w, const long h) {
	if (l >= w && l >= h) {
		return 2*w+2*h;
	}
	else if (w >= l && w >= h) {
		return 2*l+2*h;
	}
	else {
		return 2*w+2*l;
	}
}

long calc_bow(const long l, const long w, const long h) {
	return l*w*h;
}


int main(void) {
	long l, w, h;
	long paper, ribbon;
	paper = ribbon = 0;
	FILE * f_input;
	char line[SIZE];
	f_input = fopen("aoc_2015_2_input.txt", "r");
	while(fgets(line, SIZE, f_input) != NULL) {
		l = atol(strtok(line, "x"));
		w = atol(strtok(NULL, "x"));
		h = atol(strtok(NULL, "x"));
		paper += calc_surface_area(l, w, h) + calc_smallest_side_area(l, w, h);
		ribbon += calc_wrapping_ribbon(l, w, h) + calc_bow(l, w, h);
//		printf("l:%ld w:%ld h:%ld paper:%ld\n", l, w, h, paper);
	}
	printf("total paper = %ld and total ribbon = %ld\n", paper, ribbon);
	return 0;
}
