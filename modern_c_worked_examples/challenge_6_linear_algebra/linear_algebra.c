/*
  Some of the most important problems for which arrays are used stem from linear algebra.
  Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
  What about Gauß elimination or iterative algorithms for matrix inversion?
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 3
#define ROWS 4

double scalar_product(size_t columns, double scalar, double A[columns]);
double vector_vector_mult(size_t columns, double A[columns], double B[columns]);
/* inplace matrix vector mult, result -> A[0->M-1][0] */
void matrix_vector_mult(size_t columns, size_t rows, double matrix[rows][columns], double const vector[columns]);
void gaussian_elimination(size_t columns, size_t rows, double matrix[rows][columns]);
void swap_row(size_t row_a_index, size_t row_b_index, size_t columns, size_t rows, double matrix[rows][columns]);
void print_matrix(size_t columns, size_t rows, double matrix[rows][columns]);

int main(int argc, char* argv[argc+1]) {
  double vector[COLS] = { -2.0, 1.0, 0.0 };
  double og_matrix[ROWS][COLS] = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0},
    {10.0, 11.0, 12.0}
  };
  double matrix[ROWS][COLS] = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0},
    {10.0, 11.0, 12.0}
  };
  swap_row(0, ROWS-1, COLS, ROWS, matrix);
  print_matrix(COLS, ROWS, matrix);
  // -- GAUSS ELIMINATION
  return EXIT_SUCCESS;
}

void print_matrix(size_t columns, size_t rows, double matrix[rows][columns]) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      printf("[%.3e]", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void gaussian_elimination(size_t columns, size_t rows, double matrix[columns][rows]) {
  // sort
    // for each column of matrix move every row with zero in current column to bottom
  for (size_t i = 0; i < columns; i++) {
    for (size_t j = i; j < rows; j++) {
      if (matrix[j][i] == 0.0) {
        swap_row(j, rows-1, columns, rows,  matrix);
      }
    }
  }
  // reduce
}

void swap_row(size_t row_a_index, size_t row_b_index, size_t columns, size_t rows, double matrix[rows][columns]) {
  double temp;
  for (size_t i = 0; i < columns; i++) {
    temp = matrix[row_a_index][i];
    matrix[row_a_index][i] = matrix[row_b_index][i];
    matrix[row_b_index][i] = temp;
  }
}

double scalar_product(size_t columns, double scalar, double a[columns]) {
  double total = 0;
  for (size_t i = 0; i < columns; i++) {
    total += a[i] * scalar;
  }
  return total;
}

double vector_vector_mult(size_t columns, double vector_a[columns], double vector_b[columns]) {
  double total = 0;
  for (size_t i = 0; i < columns; i++) {
    total += vector_a[i] * vector_b[i];
  }
  return total;
}

/* inplace matrix vector mult, result -> A[0->M-1][0]*/
void matrix_vector_mult(size_t columns, size_t rows, double matrix[rows][columns], double const vector[columns]) {
  for (size_t i = 0; i < rows; i++) {
    double total = 0.0;
    for (size_t j = 0; j < columns; j++) {
      total += matrix[i][j] * vector[j];
    }
    matrix[i][0] = total;
  }
}
