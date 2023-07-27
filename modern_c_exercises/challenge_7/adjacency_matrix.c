/*
The adjacency matrix of a graph G is a matrix A that holds a value true or false in element A[i][j] if there is an arc from node i to node j.
    -- every row is a node on the tree
    -- every element of that row is the other nodes
At this point, can you use an adjacency matrix to conduct a breadth-first search in a graph G?
Can you find connected components?
    -- isn't this intrinsic in the adjacency graph?
Can you find a spanning tree?
    -- tf is a spanning tree?
    -- tree: any two node are connect by **exactly** on edge
    so it's a sub-graph where the nodes of the tree are the ones connected once?
*/
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ELEMENTS 5

void print_array(size_t n, size_t array[n]) {
    for (size_t i = 0; i < n; ++i) {
        printf("array[%zu]: %zu ", i, array[i]);
    }
    printf("\n\n");
}

size_t search_array(size_t key, size_t n_elem, size_t array[n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        if (array[i] == key) {
            return TRUE;
        }
    }
    return FALSE;
}

size_t dfs_matrix(size_t key, size_t row, size_t n_elem, size_t matrix[n_elem][n_elem]) {
    size_t to_search[n_elem];
    size_t searched[n_elem];
    size_t ts_e = 0, s_e = 0;
    size_t curr;
    for (size_t i = 0; i < n_elem; ++i) {
        searched[i] = SIZE_MAX; // set all of searched into garbage value so no accidental hits
    }
    to_search[ts_e] = row;
    ++ts_e; //load the first item into to search
    while (ts_e) { //while # of to search elements is non-zero
        curr = to_search[ts_e-1];
        --ts_e; //load latest ts_e into curr
        if (!search_array(curr, n_elem, searched)) { //if curr has not already been searched
            if (curr == key) { //if curr is key, done
                return TRUE;
            } else { //else add curr to searched array
                for (size_t i = 0; i < n_elem; ++i) { //add all linked nodes to be searched
                    if (matrix[curr][i] == TRUE) {
                        to_search[ts_e] = i;
                        ++ts_e;
                    }
                }
                searched[s_e] = curr; //add curr to searched
                ++s_e;
            }
        }
    }
    return FALSE;
}

size_t has_spanning_tree(size_t n_elem, size_t matrix[n_elem][n_elem]) {
}

int main(void) {
    size_t adjacency[ELEMENTS][ELEMENTS] = {{FALSE, FALSE, TRUE, FALSE, TRUE},
                                            {FALSE, FALSE, FALSE, TRUE, FALSE},
                                            {TRUE, FALSE, FALSE, FALSE, TRUE},
                                            {FALSE, TRUE, FALSE, FALSE, FALSE},
                                            {FALSE, FALSE, TRUE, FALSE, FALSE}};
    assert(dfs_matrix(1, 3, ELEMENTS, adjacency) == TRUE);
    assert(dfs_matrix(4, 0, ELEMENTS, adjacency) == TRUE);
    assert(dfs_matrix(4, 2, ELEMENTS, adjacency) == TRUE);
    assert(dfs_matrix(4, 1, ELEMENTS, adjacency) == FALSE);

    return 0;
}
