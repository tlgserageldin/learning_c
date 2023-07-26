/*
CHALLENGE 6 Linear algebra
Some of the most important problems for which arrays are used stem from linear algebra.
Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
-- Only vector-vector i dont know how to return an array
-- for the matrx-vector i can just edit the vector inplace, so technically i can ig
What about Gauß elimination or iterative algorithms for matrix inversion?
*/
#include <assert.h>
#include <tgmath.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

double vector_prod(size_t N, double arr_1[N], double arr_2[N]);
void vector_matrix_prod(size_t N, size_t M, double vector[N], double matrix[N][M]);
void gauss_elim_partial_pivot(size_t N, size_t M, double matrix[M][N]);
void transpose_matrix(size_t N, double matrix[N][N]);
void print_matrix(size_t cols, size_t rows, double matrix[rows][cols]);
void print_vector(size_t len, double vector[len]);
void swap_rows(size_t N, size_t M, size_t row1, size_t row2, double matrix[M][N]);
void invert_matrix(size_t N, double matrix[N][N]);
double det_matrix(size_t N, double matrix[N][N]);

#define TRUE 1
#define FALSE 0

#define MROWS 4
#define MCOLS 4


int main(void) {
    double matrix[MROWS][MCOLS] = {{1.0, 2.0, 3.0, 4.0},
                                   {3.0, 2.0, 1.0, 1.0},
                                   {3.0, 1.0, 2.0, 4.0},
                                   {4.0, 2.0, 3.0, 1.0}};
    print_matrix(MROWS, MCOLS, matrix);
    invert_matrix(MROWS, matrix);
    print_matrix(MROWS, MCOLS, matrix);
    return 0;
}

/*
    plus a times the determinant of the matrix that is not in a's row or column,
    minus b times the determinant of the matrix that is not in b's row or column,
    plus c times the determinant of the matrix that is not in c's row or column,
    minus d times the determinant of the matrix that is not in d's row or column,
*/
// determinant of a matrix
double det_matrix(size_t N, double matrix[N][N]) {
    if (N == 1) {
        return matrix[0][0];
    } else if (N == 2) {
        return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
    } else {
        double total = 0;
        double sub_matrix[N-1][N-1]; //this should be matrix of all elems not in i-th row/col
        for (size_t i = 0; i < N; ++i) { //total += i * det_matrix(N-1, submatrix);
            for (size_t j = 0, k = 0; j < N; ++j) { //populate submatrix
                if (j != 0) {
                    for (size_t l = 0, g = 0; l < N; ++l) {
                        if (l != i) {
                            sub_matrix[k][g] = matrix[j][l];
                            ++g;
                        }
                    }
                    ++k;
                }       
            }
            if (i % 2 == 0) {
                total += matrix[0][i] * det_matrix(N-1, sub_matrix);
            } else {
                total -= matrix[0][i] * det_matrix(N-1, sub_matrix);
            }
        }
        return total;
    }
}

// invert a square matrix
// https://en.wikipedia.org/wiki/Invertible_matrix#Inversion_of_3_%C3%97_3_matrices
void invert_matrix(size_t N, double matrix[N][N]) {
    double det = det_matrix(N, matrix);
    if (det == 0.0f) {
        printf("matrix is singular...\n\n");
    } else {
        // create aug_matrix
        double matrix_prime[N][N];
        double sub_matrix[N-1][N-1];
        size_t count;
        for (size_t i = 0; i < N; ++i) {
            if (i % 2 == 0) {
                count = 0;
            } else {
                count = 1;
            }
            for (size_t j = 0; j < N; ++j) { // go through every location in matrix
                for (size_t k = 0, ki = 0; k < N; ++k) { //create submatrix of that location
                    if (k != i) {
                        for (size_t l = 0, li = 0; l < N; ++l) {
                            if (l != j) {
                                sub_matrix[ki][li] = matrix[k][l];
                                ++li;
                            }
                        }
                        ++ki;
                    }
                }
                if (count % 2 == 0) {
                    matrix_prime[i][j] = det_matrix(N-1, sub_matrix);
                } else {
                    matrix_prime[i][j] = det_matrix(N-1, sub_matrix) * -1;
                }
                ++count;
            }
        }
        transpose_matrix(N, matrix_prime);
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] = (1/det) * matrix_prime[i][j];
            }
        }
    }
}

// vector-vector dot product
double vector_prod(size_t N, double arr_1[N], double arr_2[N]) {
    double res = 0;
    for (size_t i = 0; i < N; ++i) {
        res += arr_1[i] * arr_2[i];
    }
    return res;
}

// vector-matrix dot product
void vector_matrix_prod(size_t N, size_t M, double vector[static N], double matrix[N][M]) {
    for (size_t i = 0; i < N; ++i) {
        double x = vector[i];
        vector[i] = 0;
        for (size_t j = 0; j < M; ++j) {
            vector[i] += x * matrix[i][j];
        }
    }
}

/*
 * echelon form notes
 *
 * basic row ops:
 *      1. swap position of rows
 *      2. multiply a row by a scalar
 *      3. add to one row the scalar multiple of another
 *
 * if row is non-zero, then "leftmost" nonzero is leading coefficient aka pivot
 * if two pivots are in same column, then use row op 3 to fix
 * arrange rows so that every non-zero row's pivot is to the right of the row above
 */
void gauss_elim_partial_pivot(size_t N, size_t M, double matrix[M][N]) {
    size_t col = 0;
    size_t row = 0;
    double scalar;
    double pivot;
    size_t pivot_row;
    while (col <= N && row <= M) {
        // find pivot for current col
        pivot = 0;
        pivot_row = 0;
        for (size_t i = row; i < M; ++i) {
            if (fabs(matrix[i][col]) > fabs(pivot)) {
                pivot = matrix[i][col];
                pivot_row = i;
            }
        }
        if (pivot) { // if not zero
            swap_rows(N, M, pivot_row, row, matrix); //swap to replace current row
            for (size_t i = row+1; i < M; ++i) { // add scalar multiple of row to elim non-zeros below pivot
                if (matrix[i][col]) { //only add scalar mult if non-zero value in col
                    scalar = matrix[i][col] / pivot;
                    if (pivot > 0.0f) {
                        scalar *= -1;
                    }
                    for (size_t j = col; j < N; ++j) { //add scalar mult of the row 
                        matrix[i][j] += matrix[row][j] * scalar;
                    }
                }
            }
            ++row;
            ++col;
        } else { //no pivots go next col
            col++;
        }
    }
}

void print_matrix(size_t cols, size_t rows, double matrix[rows][cols]) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("matrix[%zu][%zu]: %lf\n", i, j, matrix[i][j]);
        }
    }
    printf("\n");
}

void print_vector(size_t len, double vector[len]) {
    for (size_t i = 0; i < len; ++i) {
        printf("vector[%zu]: %lf\n", i, vector[i]);
    }
    printf("\n");
}

void swap_rows(size_t N, size_t M, size_t row1, size_t row2, double matrix[M][N]) {
    double buff[N];
    for (size_t i = 0; i < N; ++i) {
        buff[i] = matrix[row1][i];
    }
    for (size_t i = 0; i < N; ++i) {
        matrix[row1][i] = matrix[row2][i];
    }
    for (size_t i = 0; i < N; ++i) {
        matrix[row2][i] = buff[i];
    }
}

// cannot return a new matrix, so can only transpose square matrices
void transpose_matrix(size_t N, double matrix[N][N]) {
    double temp_matrix[N][N];
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            temp_matrix[j][i] = matrix[i][j];
        }
    }
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            matrix[i][j] = temp_matrix[i][j];
        }
    }
}
