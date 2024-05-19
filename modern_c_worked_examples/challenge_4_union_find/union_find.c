/*
The Union-Find problem deals with the representation of partitions over a base set.
We will identify the elements of the base set using the numbers 0, 1, ... and will represent partitions with a forest data structure 
    - A forest is an undirected graph in which any two vertices are connected by at most one path.
    - Meaning for N elements there will be an array of N elements, where the ith value of the array is the "parent"
    - or node it's attached to
where each element has a “parent” that is another element inside the same partition. 
Each set in such a partition is identified by a designated element called the root of the set.
    - the "root" of the set is the element whos parent is itself
    

We want to perform two principal operations:
A Find operation receives one element of the ground set and returns the root of the corresponding set.
A Union operation receives two elements and merges the two sets to which these elements belong into one.
Can you implement a forest data structure in an index table of base type size_t called parent? 
    - index table just means that for some list of numbered items there is data associated with that numbered item (index of array)
Here, a value in the table SIZE_MAX would mean a position represents a root of one of the trees;
    another number represents position of the parent of the corresponding tree. 
One of the important features to start the implementation is an initialization function that makes parent the singleton partition:
    that is, the partition where each element is the root of its own private set.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define ELEMENTS 5

/*A Find operation receives one element of the ground set and returns the root of the corresponding set.
  Base case = parent[A] = SIZE_T_MAX */
size_t Find(size_t A, size_t parent_arr[static 1]);

/*A Union operation receives two elements and merges the two sets to which these elements belong into one.
  Join A -> B*/
void Union(size_t A, size_t B, size_t parent_arr[static 1]);

/*Make the parent set into the singleton parent*/
void Init(size_t n, size_t parent_arr[n]);

/*Print parrent_arr of n elements*/
void print(size_t n, size_t parrent_arr[n]);

int main(int argc, char* argv[argc+1]) {
    size_t parent[ELEMENTS];
    Init(ELEMENTS, parent);
    print(ELEMENTS, parent);
    Union(3, 1, parent);
    print(ELEMENTS, parent);
    Union(2, 1, parent);
    print(ELEMENTS, parent);
    Union(4, 3, parent);
    print(ELEMENTS, parent);
    return EXIT_SUCCESS;
}

void Init(size_t n, size_t parent_arr[n]) {
    for (size_t i = 0; i < n; i++) {
        parent_arr[i] = SIZE_T_MAX;
    }
}

void Union(size_t A, size_t B, size_t parent_arr[static 1]) {
    parent_arr[A] = B;
}

size_t Find(size_t A, size_t parent_arr[static 1]) {
    size_t As_parent = parent_arr[A];
    switch (As_parent) {
        case SIZE_T_MAX:
            return A;
        default:
            return Find(As_parent, parent_arr);
    }
}

void print(size_t n, size_t parrent_arr[n]) {
    for (size_t i = 0; i < n; i++) {
        printf("%zu: %zu\n", i, parrent_arr[i]);
    }
    printf("\n");
}
