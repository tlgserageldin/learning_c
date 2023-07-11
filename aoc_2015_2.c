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


int main(void) {
	long l, w, h;
	long small_area, surface_area, paper, total_paper;
	total_paper = 0;
	FILE * f_input;
	char line[SIZE];
	f_input = fopen("aoc_2015_2_input.txt", "r");
	while(fgets(line, SIZE, f_input) != NULL) {
		l = atol(strtok(line, "x"));
		w = atol(strtok(NULL, "x"));
		h = atol(strtok(NULL, "x"));
		small_area = calc_smallest_side_area(l, w, h);
		surface_area = calc_surface_area(l, w, h);
		paper = small_area + surface_area;
//		printf("l:%ld w:%ld h:%ld paper:%ld\n", l, w, h, paper);
		total_paper += paper;
	}
	printf("total_paper = %ld\n", total_paper);
	return 0;
}
