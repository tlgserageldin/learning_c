/*
  Some of the most important problems for which arrays are used stem from linear algebra.
  Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
  What about Gauß elimination or iterative algorithms for matrix inversion?
*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define COLS 3
#define ROWS 4

double scalar_product(size_t N, double scalar, double A[N]);
double vector_vector_mult(size_t N, double A[N], double B[N]);
/* inplace matrix vector mult, result -> A[0->M-1][0] */
void matrix_vector_mult(size_t N, size_t M, double A[M][N], double const B[N]);
void gaussian_elimination(size_t N, size_t M, double A[M][N]);

int main(int argc, char* argv[argc+1]) {
  double vector[COLS] = { -2.0, 1.0, 0.0 };
  double matrix[ROWS][COLS] = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0},
    {10.0, 11.0, 12.0}
  };
  matrix_vector_mult(3, 4, matrix, vector);
  double expected[ROWS] = { 0, -3.0, -6.0, -9.0 };
  double result[ROWS];
  for (size_t i = 0; i < ROWS; i++) {
    result[i] = matrix[i][0];
  }
  assert(!memcmp(result, expected, sizeof(double)*COLS));
  // -- GAUSS ELIMINATION
  return EXIT_SUCCESS;
}

void gaussian_elimination(size_t N, size_t M, double A[M][N]) {
  // sort
    // for each column of matrix move every row with zero in current column to bottom
  // reduce
}

double scalar_product(size_t N, double scalar, double A[N]) {
  double total = 0;
  for (size_t i = 0; i < N; i++) {
    total += A[i] * scalar;
  }
  return total;
}

double vector_vector_mult(size_t N, double A[N], double B[N]) {
  double total = 0;
  for (size_t i = 0; i < N; i++) {
    total += A[i] * B[i];
  }
  return total;
}

/* inplace matrix vector mult, result -> A[0->M-1][0]*/
void matrix_vector_mult(size_t N, size_t M, double A[M][N], double const B[N]) {
  for (size_t i = 0; i < M; i++) {
    double total = 0.0;
    for (size_t j = 0; j < N; j++) {
      total += A[i][j] * B[j];
    }
    A[i][0] = total;
  }
}
