/*
i dont know linear algebra so going to have to read alot for this
*/

/*
CHALLENGE 6 Linear algebra
Some of the most important problems for which arrays are used stem from linear algebra.
Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
-- Only vector-vector i dont know how to return an array
-- for the matrx-vector i can just edit the vector inplace, so technically i can ig
What about Gauß elimination or iterative algorithms for matrix inversion?
*/
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MOVELEFT -1
#define MOVERIGHT 1
#define SAME 0

// vector-vector dot product
long vector_prod(size_t N, long arr_1[static N], long arr_2[static N]) {
    long res = 0;
    for (size_t i = 0; i < N; ++i) {
        res += arr_1[i] * arr_2[i];
    }
    return res;
}

// vector-matrix dot product
// dont know how to return a array yet so will just edit vector in place
void vector_matrix_prod(size_t N, size_t M, double vector[static N], double matrix[static N][M]) {
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
 * if two leading coeff are in same column, then use row op 3 to fix
 * arrange rows so that every non-zero row's pivot is to the right of the row above
 */
void gauss_elim(size_t N, size_t M, long matrix[N][M]) {
}

int main(void) {
    double matrix[3][3] = {{1.0, 2.0, 3.0},
                           {4.0, 5.0, 6.0},
                           {7.0, 8.0, 9.0}};
    double vector[3] = { 1.0, 2.0, 3.0 };
    vector_matrix_prod(3, 3, vector, matrix);
    for (size_t i = 0; i < 3; ++i) {
        printf("vector[%zu] = %f\n", i, vector[i]);
    }
    return 0;
}
