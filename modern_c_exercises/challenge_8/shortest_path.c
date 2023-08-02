/*
Extend the idea of an adjacency matrix of a graph G to a distance matrix D that holds the distance when going from point i to point j.
Mark the absence of a direct arc with a very large value, such as SIZE_MAX.
Can you find the shortest path between two nodes x and y given as an input?
*/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ELEMENTS 4

// search an size_t array for key
size_t search_array(size_t key, size_t n_elem, size_t array[n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        if (array[i] == key) {
            return TRUE;
        }
    }
    return FALSE;
}

// print array of n_elem elements
void print_array(size_t n_elem, size_t array[n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        printf("array[%zu]: %zu ", i, array[i]);
    }
    printf("\n\n");
}

// print a square matrix
void print_matrix(size_t n_elem, size_t matrix[n_elem][n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        for (size_t j = 0; j < n_elem; ++j) {
            printf("matrix[%zu][%zu]=%zu ", i, j, matrix[i][j]);
        }
        printf("\n\n");
    }
}

// find shortest path between two nodes of an distance graph
void shortest_path(size_t start, size_t finish, size_t n_elem, size_t path[n_elem], size_t matrix[n_elem][n_elem]) {
    size_t parent[n_elem];
    size_t cost[n_elem];
    size_t searched[n_elem];
    size_t to_search[n_elem];
    size_t path_e = 0, to_search_e = 0, searched_e = 0, current = 0;
    for (size_t i = 0; i < n_elem; ++i) {
        cost[i] = SIZE_MAX;
        path[i] = SIZE_MAX;
        parent[i] = SIZE_MAX;
    }
    to_search[to_search_e] = start;
    ++to_search_e;
    cost[start] = 0;
    while (to_search_e) {
        current = to_search[--to_search_e];
        if (!search_array(current, searched_e, searched)) {
            for (size_t i = 0; i < n_elem; ++i) {
                if (matrix[current][i] != SIZE_MAX) {
                    if (cost[current] + matrix[current][i] < cost[i]) {
                        parent[i] = current;
                        cost[i] = cost[current] + matrix[current][i];
                    }
                    if (!search_array(i, to_search_e, to_search)) {
                        to_search[to_search_e] = i;
                        ++to_search_e;
                    }
                }
            }
        }
        searched[searched_e] = current;
        searched_e++;
    }
    path[0] = finish;
    for (size_t i = 1; i < n_elem; ++i) {
        path[i] = parent[path[i-1]];
        ++path_e;
        if (!parent[path[i-1]]) {
            break;
        }
    }
}

int main(void) {
    size_t distance[ELEMENTS][ELEMENTS] = {{SIZE_MAX, 6, 2, SIZE_MAX},
                                           {6, SIZE_MAX, 3, 1},
                                           {2, 3, SIZE_MAX, 5},
                                           {SIZE_MAX, 1, 5, SIZE_MAX}};
    size_t path[ELEMENTS];
    shortest_path(0, 3, ELEMENTS, path, distance);
    print_array(ELEMENTS, path);
    return 0;
}
