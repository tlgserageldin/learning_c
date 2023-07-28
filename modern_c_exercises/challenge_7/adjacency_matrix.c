/*
The adjacency matrix of a graph G is a matrix A that holds a value true or false in element A[i][j] if there is an arc from node i to node j.
    -- every row is a node on the tree
    -- every element of that row is the other nodes + itself for simplicity
At this point, can you use an adjacency matrix to conduct a breadth-first search in a graph G?
    -- yes.
Can you find connected components?
    -- isn't this intrinsic in the adjacency graph?
    -- OOO this means find all nodes that are connected
Can you find a spanning tree?
    -- tf is a spanning tree?
    -- tree: any two node are connect by **exactly** on edge
    so it's a sub-graph where the nodes of the tree are the ones connected once?
    i cannot return arrays yet, what is the return type? do i pass in an array?
    i will pass in an array.
*/
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ELEMENTS 5

// depth first search of a adjacency matrix
size_t dfs_matrix(size_t key, size_t node, size_t n_elem, size_t matrix[n_elem][n_elem]);
// search an size_t array for key
size_t search_array(size_t key, size_t n_elem, size_t array[n_elem]);
// print array of n_elem elements
void print_array(size_t n_elem, size_t array[n_elem]);
// edit the passed tree_arr in place. will fill non-used array elems with SIZE_MAX
void find_spanning_tree(size_t n_elem, size_t tree_arr[n_elem], size_t matrix[n_elem][n_elem]);
// return number of connect nodes to any given node
size_t count_connected_nodes(size_t node, size_t n_elem, size_t matrix[n_elem][n_elem]);

int main(void) {
    size_t adjacency[ELEMENTS][ELEMENTS] = {{FALSE, FALSE, TRUE, FALSE, TRUE},
                                            {FALSE, FALSE, FALSE, TRUE, FALSE},
                                            {TRUE, FALSE, FALSE, FALSE, TRUE},
                                            {FALSE, TRUE, FALSE, FALSE, FALSE},
                                            {FALSE, FALSE, TRUE, FALSE, FALSE}};
    assert(count_connected_nodes(1, ELEMENTS, adjacency) == 2);
    assert(count_connected_nodes(0, ELEMENTS, adjacency) == 3);
    return 0;
}

// print array of n_elem elements
void print_array(size_t n_elem, size_t array[n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        printf("array[%zu]: %zu ", i, array[i]);
    }
    printf("\n\n");
}

// edit the passed tree_arr in place. will fill non-used array elems with SIZE_MAX
void find_spanning_tree(size_t n_elem, size_t tree_arr[n_elem], size_t matrix[n_elem][n_elem]) {
}

// return number of connect nodes to any given node
size_t count_connected_nodes(size_t node, size_t n_elem, size_t matrix[n_elem][n_elem]){
    size_t to_search[n_elem];
    size_t searched[n_elem];
    size_t ts_e = 0, s_e = 0;
    size_t curr, count = 0;
    for (size_t i = 0; i < n_elem; ++i) {
        searched[i] = SIZE_MAX; // set all of searched into garbage value so no accidental hits
    }
    to_search[ts_e] = node;
    ++ts_e; //load the first item into to search
    while (ts_e) { //while # of to search elements is non-zero
        curr = to_search[ts_e-1];
        --ts_e; //load latest ts_e into curr
        if (!search_array(curr, n_elem, searched)) { //if curr has not already been searched
            ++count;
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
    return count;
}

// search an size_t array for key
size_t search_array(size_t key, size_t n_elem, size_t array[n_elem]) {
    for (size_t i = 0; i < n_elem; ++i) {
        if (array[i] == key) {
            return TRUE;
        }
    }
    return FALSE;
}

// depth first search of a adjacency matrix
size_t dfs_matrix(size_t key, size_t node, size_t n_elem, size_t matrix[n_elem][n_elem]) {
    size_t to_search[n_elem];
    size_t searched[n_elem];
    size_t ts_e = 0, s_e = 0;
    size_t curr;
    for (size_t i = 0; i < n_elem; ++i) {
        searched[i] = SIZE_MAX; // set all of searched into garbage value so no accidental hits
    }
    to_search[ts_e] = node;
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
