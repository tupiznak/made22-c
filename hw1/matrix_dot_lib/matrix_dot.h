#ifndef HW1_MATRIX_DOT_LIB_MATRIX_DOT_H_
#define HW1_MATRIX_DOT_LIB_MATRIX_DOT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Matrix {
    int **arr;
    int rows;
    int columns;
} Matrix;

typedef struct Operation {
    Matrix *matrix;
    bool success;
} Operation;


Matrix Matrix_constructor(int rows, int columns, bool with_zeros);

Matrix Matrix_empty_constructor(int rows, int columns);

Matrix Matrix_zeros_constructor(int rows, int columns);

void Matrix_destructor(Matrix matrix);

bool Matrix_is_can_dot(Matrix matrix_a, Matrix matrix_b);

bool Matrix_is_equal(Matrix matrix_a, Matrix matrix_b);

Operation Matrix_compute_new_element(Matrix matrix_a, Matrix matrix_b, Matrix matrix_result,
                                     int processed_row, int processed_col);

Operation Matrix_dot(Matrix matrix_a, Matrix matrix_b);

#endif  // HW1_MATRIX_DOT_LIB_MATRIX_DOT_H_
