#ifndef MATRIX_DOT_H
#define MATRIX_DOT_H

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

Matrix Matrix_destructor(Matrix matrix);

bool Matrix_is_can_dot(Matrix matrix_a, Matrix matrix_b);

bool Matrix_is_equal(Matrix matrix_a, Matrix matrix_b);

Operation Matrix_compute_new_element(Matrix matrix_a, Matrix matrix_b, Matrix matrix_result,
                                     int processed_row, int processed_col);

Operation Matrix_dot(Matrix matrix_a, Matrix matrix_b);

#endif // MATRIX_DOT_H
