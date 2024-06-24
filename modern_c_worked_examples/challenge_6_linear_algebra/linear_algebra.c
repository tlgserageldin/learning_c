/*
Some of the most important problems for which arrays are used stem from linear algebra.
Can you write functions that do vector-to-vector or matrix-to-vector products at this point?
What about Gauß elimination or iterative algorithms for matrix inversion?
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define COLS 3
#define ROWS 4

#define TRUE 1
#define FALSE 0

void print_vector( const size_t cols, const size_t vector[cols] ) {
    for ( size_t i = 0; i < cols; i++ ) {
        printf( "[%zu]", vector[i] );
    }
    printf( "\n" );
}

void print_matrix( const size_t cols, const size_t rows, const double matrix[rows][cols] ) {
    for ( size_t i = 0; i < rows; i++ ) {
        for ( size_t j = 0; j < cols; j++ ) {
            printf( "[%.3e]", matrix[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

void add_multiple_of_row( const size_t cols, const size_t rows, const size_t multiple,
                          const size_t row_source, const size_t row_target,
                          double matrix[rows][cols] ) {
    for ( size_t i = 0; i < cols; i++ ) {
        matrix[row_target][i] += multiple * matrix[row_source][i];
    }
}

void swap_row( const size_t row_a_index, const size_t row_b_index, const size_t cols,
               const size_t rows, double matrix[rows][cols] ) {
    double temp;
    for ( size_t i = 0; i < cols; i++ ) {
        temp = matrix[row_a_index][i];
        matrix[row_a_index][i] = matrix[row_b_index][i];
        matrix[row_b_index][i] = temp;
    }
}

void bump_row_to_bottom( const size_t cols, const size_t rows, const size_t row_index, double matrix[rows][cols] ) {
    for ( size_t i = 0; i < rows - (row_index + 1); i++ ) {
        swap_row(i, i+1, cols, rows, matrix);
    }
}

double scalar_product( const size_t cols, const double scalar, const double a[cols] ) {
    double total = 0;
    for ( size_t i = 0; i < cols; i++ ) {
        total += a[i] * scalar;
    }
    return total;
}

double vector_vector_mult( const size_t cols, const double vector_a[cols], const double vector_b[cols] ) {
    double total = 0;
    for ( size_t i = 0; i < cols; i++ ) {
        total += vector_a[i] * vector_b[i];
    }
    return total;
}

/*
inplace matrix vector mult, result -> A[0->M-1][0]
the book hasnt covered pointers at this point
so i wont use them here
*/
void matrix_vector_mult( const size_t cols, const size_t rows, double matrix[rows][cols], double const vector[cols] ) {
    for ( size_t i = 0; i < rows; i++ ) {
        double total = 0.0;
        for ( size_t j = 0; j < cols; j++ ) {
            total += matrix[i][j] * vector[j];
        }
        matrix[i][0] = total;
    }
}

size_t count_leading_zeros( const size_t cols, const size_t index, const double matrix[1][cols] ) {
    size_t count = 0;
    for ( size_t curr_col = 0; curr_col < cols; curr_col++ ) {
        if ( matrix[index][curr_col] == 0.0 ) {
            count++;
        } else {
            break;
        }
    }
    return count;

}

int is_echelon_form( const size_t cols, const size_t rows, const double matrix[rows][cols]) {
    /* find first pivot */
    size_t row = 0;
    size_t col = 0;
    for ( int i = rows - 1; i >= 0; i-- ) {
        for ( int j = 0; j < cols - 1; j++ ) {
            if ( matrix[i][j] != 0.0 ) {
                row = i;
                col = j;
                goto exit_loops;
            }
        }
    }
    return TRUE;
exit_loops:

    /* check if the leading coefficient above is to the left */
    for ( ;; ) {
        size_t prev_col = col;
        row--;
        for ( int i = col; i >= 0; i-- ) {
            if ( matrix[row][i] != 0.0 ) {
                col = i;
            }
        }
        if ( col == prev_col ) {
            return FALSE; 
        }
        if ( !row ) {
            return TRUE;
        }
    }
}


/*
    Swapping two rows,
    Multiplying a row by a nonzero number,
    Adding a multiple of one row to another row.
*/
void gaussian_elimination( const size_t cols, const size_t rows, double matrix[rows][cols] ) {
}

int main( int argc, char* argv[argc+1] ) {
    double test_matrix_1[ROWS][COLS] = {
        {4.0, 5.0, 6.0},
        {0.0, 2.0, 0.0},
        {0.0, 0.0, 9.0},
        {0.0, 0.0, 0.0}
    };
    double test_matrix_2[ROWS][COLS] = {
        {0.0, 0.0, 0.0},
        {4.0, 0.0, 6.0},
        {1.0, 0.0, 9.0},
        {0.0, 11.0, 12.0}
    };
    assert( is_echelon_form( COLS, ROWS, test_matrix_1) );
    assert( !is_echelon_form( COLS, ROWS, test_matrix_2) );
    return EXIT_SUCCESS;
}
