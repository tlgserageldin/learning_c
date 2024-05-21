#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define UNREACHABLE -1

enum item { book, lp, poster, guitar, drums, piano, item_num };

typedef struct node node;
struct node {
  int cost;
  size_t parent;
};

int cheapest_edge_value(size_t elements, size_t node, int edge_arr[static 1][elements]) {
  int value = INT_MAX;
  for (size_t i = 0; i < elements; i++) {
    if (edge_arr[node][i] != UNREACHABLE && edge_arr[node][i] < value) {
      value = edge_arr[node][i];
    }
  }
  return value;
}

int cheapest_edge(size_t elements, size_t node, int edge_arr[static 1][elements]) {
  int value = INT_MAX;
  for (size_t i = 0; i < elements; i++) {
    if (edge_arr[node][i] != UNREACHABLE && edge_arr[node][i] < value) {
      value = i;
    }
  }
  return value;
}


size_t dijkstras(size_t N, int edge_arr[N][N], int start, int end) {
  node array[N];
  /* set every byte of array to 0 */
  for (size_t i = 0; i < N; i++) {
    array[i].cost = INT_MAX;
    array[i].parent = 0;
  }
  for (size_t i = 0; i < N; i++) {
    array[i].cost = cheapest_edge_value(N, i, edge_arr);
    array[i].parent = cheapest_edge(N, i, edge_arr);
  }
}

int main(int argc, char* argv[argc+1]) {
  int edge[item_num][item_num];
  for (size_t i = 0; i < item_num; i++) {
    for (size_t f = 0; f < item_num; f++) {
      edge[i][f] = UNREACHABLE;
    }
  }
  edge[book][lp] = 5; edge[book][poster] = 0;
  edge[lp][drums] = 20; edge[lp][guitar] = 15;
  edge[poster][guitar] = 30; edge[poster][drums] = 35;
  edge[guitar][piano] = 20; 
  edge[drums][piano] = 10;
  return EXIT_SUCCESS;
}
