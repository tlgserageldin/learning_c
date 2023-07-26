// the "base set" is just the indicies of the array
// the value of any given index is the parent of that cell
// when the index == value its the root
// eg
// 		parent[4] = 4 <= root
// 		parent[2] = 3 <= 3 is the parent of 2
// 		parent[3] = 7 <= 7 is the parent of 3
// 		parent[7] = 7 <= root
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define TABLESIZE 10

void init_parent(size_t n, size_t parent[static n]) { //we are going to access n elements of parent n
	for (size_t i = 0; i < n; ++i) {
		parent[i] = i;
	}
}

void print_parent(size_t n, size_t parent[static n]) { //we are going to access n elements of parent n
	for (size_t i = 0; i < n; ++i) {
		printf("parent[%zu] = %zu\n", i, parent[i]);
	}
}

size_t find_root(size_t n, size_t parent[static n], size_t i) { // for a given index(i) find its root which is when parent[i] = i
	if (i >= n) {
		printf("cannot find element out of range\n\n");
		return SIZE_MAX; //some obviously wrong value
	}
	if (parent[i] == i) {
		return i;
	} else {
		return find_root(n, parent, parent[i]);
	
	}
}

void find_replace(size_t n, size_t parent[static n], size_t i, size_t value) {
	if (i >= n) {
		printf("cannot find element out of range\n\n");
		return;
	}
	if (parent[i] == i) {
		parent[i] = value;
	} else {
		size_t prev_parent = parent[i];
		parent[i] = value;
		find_replace(n, parent, prev_parent, value);
	}
}

void find_compress(size_t n, size_t parent[static n], size_t i) {
	if (i >= n) {
		printf("cannot find element out of range\n\n");
		return;
	}
	if (i == parent[i]) {
		return;
	} else {
		size_t prev_parent = parent[i];
		parent[i] = find_root(n, parent, prev_parent);
		find_compress(n, parent, prev_parent);
	}
}

void Union(size_t n, size_t parent[static n], size_t i_one, size_t i_two) {
	if (i_one >= n || i_two >= n) {
		printf("cannot find element out of range\n\n");
		return;
	}
	find_compress(n, parent, i_one);
	find_replace(n, parent, i_two, i_one);
}

int main(void) {
	size_t parent[TABLESIZE];
	init_parent(TABLESIZE, parent);
	find_replace(TABLESIZE, parent, 5, 4);
	find_replace(TABLESIZE, parent, 4, 3);
	find_replace(TABLESIZE, parent, 3, 2);
	find_replace(TABLESIZE, parent, 2, 1);
	find_replace(TABLESIZE, parent, 1, 0);
	find_replace(TABLESIZE, parent, 6, 7);
	find_replace(TABLESIZE, parent, 7, 8);
	find_replace(TABLESIZE, parent, 8, 9);
	print_parent(TABLESIZE, parent);
	Union(TABLESIZE, parent, 5, 6);
	print_parent(TABLESIZE, parent);
	for (size_t i = 0; i < TABLESIZE; ++i) {
		assert(find_root(TABLESIZE, parent, i) == 0);
	}
	return 0;
}
