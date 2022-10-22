#include "matrix_dot.h"

Matrix Matrix_constructor(int rows, int columns, bool with_zeros) {
    int **arr = (int **) malloc(rows * sizeof(int *));
    if (with_zeros) {
        for (int i = 0; i < rows; ++i) {
            arr[i] = (int *) calloc(columns, sizeof(int));
        }
    } else {
        for (int i = 0; i < rows; ++i) {
            arr[i] = (int *) malloc(columns * sizeof(int));
        }
    }
    Matrix matrix = {
            .arr = arr,
            .rows = rows,
            .columns = columns,
    };
    return matrix;
}

Matrix Matrix_empty_constructor(int rows, int columns) {
    return Matrix_constructor(rows, columns, false);
}

Matrix Matrix_zeros_constructor(int rows, int columns) {
    return Matrix_constructor(rows, columns, true);
}

void Matrix_destructor(Matrix matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        free(matrix.arr[i]);
    }
    free(matrix.arr);
}

bool Matrix_is_can_dot(Matrix matrix_a, Matrix matrix_b) {
    return matrix_a.columns == matrix_b.rows;
}

bool Matrix_is_equal(Matrix matrix_a, Matrix matrix_b) {
    if (matrix_a.columns != matrix_b.columns || matrix_a.rows != matrix_b.rows) {
        return false;
    }
    for (int i = 0; i < matrix_a.rows; ++i) {
        for (int j = 0; j < matrix_a.columns; ++j) {
            if (matrix_a.arr[i][j] != matrix_b.arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Operation Matrix_compute_new_element(Matrix matrix_a, Matrix matrix_b, Matrix matrix_result,
                                     int processed_row, int processed_col) {
    Operation result;
    result.matrix = NULL;
    if (!Matrix_is_can_dot(matrix_a, matrix_b)) {
        result.success = false;
        return result;
    }
    if (processed_row >= matrix_a.rows) {
        result.success = false;
        return result;
    }
    if (processed_col >= matrix_a.columns) {
        result.success = false;
        return result;
    }

    int sum = 0;
    for (int i = 0; i < matrix_a.columns; ++i) {
        sum += matrix_a.arr[processed_row][i] * matrix_b.arr[i][processed_col];
    }
    matrix_result.arr[processed_row][processed_col] = sum;
    result.success = true;
    return result;
}

Operation Matrix_dot(Matrix matrix_a, Matrix matrix_b) {
    Operation result;
    result.matrix = NULL;
    result.success = false;
    if (matrix_a.columns <= 0 || matrix_a.rows <= 0 || matrix_b.columns <= 0 || matrix_b.rows <= 0) {
        return result;
    }
    if (!Matrix_is_can_dot(matrix_a, matrix_b)) {
        return result;
    }

    Matrix *matrix_result = (Matrix *) malloc(sizeof(Matrix));
    *matrix_result = Matrix_empty_constructor(matrix_a.rows, matrix_b.columns);
    Operation element_operation;
    for (int i = 0; i < matrix_a.rows; ++i) {
        for (int j = 0; j < matrix_b.columns; ++j) {
            element_operation = Matrix_compute_new_element(matrix_a, matrix_b, *matrix_result, i, j);
            if (!element_operation.success) {
                Matrix_destructor(*matrix_result);
                free(matrix_result);
                return result;
            }
        }
    }
    result.success = true;
    result.matrix = matrix_result;
    return result;
}
