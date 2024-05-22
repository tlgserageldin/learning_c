#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

enum node { A, B, C, D, node_num };

int nodes_to_visit(size_t N, int visited[N]) {
  for (size_t i = 0; i < N; i++) {
    switch (visited[i]) {
      case TRUE:
        break;
      default:
        return TRUE;
    }
  }
  return FALSE;
}

int dijkstras(size_t N, int start, int end, int edge[N][N]) {
  size_t cost[N];
  size_t parent[N];
  size_t visited[N];
  for (size_t i = 0; i < 0; i++) {
    cost[i] = parent[i] = SIZE_T_MAX;
    visited[i] = FALSE;
  }
  cost[start] = 0;
  parent[start] = start;
  visited[start] = TRUE;
  while (nodes_to_visit(node_num, visited)) {
  }
  return 0;
}

int main(int argc, char* argv[argc+1]) {
  int edge[node_num][node_num];
  for (size_t i = 0; i < node_num; i++) {
    for (size_t f = 0; i < node_num; i++) {
      edge[i][f] = SIZE_T_MAX;
    }
  }
  edge[A][B] = 6; edge[A][C] = 2;
  edge[B][D] = 1; 
  edge[C][B] = 3; edge[C][D] = 5;
  int start = A;
  int end = D;
  int weight_of_shortest_path = dijkstras(node_num, start, end, edge);
  return EXIT_SUCCESS;
}
