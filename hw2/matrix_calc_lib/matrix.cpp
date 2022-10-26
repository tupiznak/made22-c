#include "matrix.h"

Matrix::~Matrix() {
    for (unsigned int i = 0; i < matrix_rows; ++i) {
        delete[] matrix_arr[i];
    }
    delete[]matrix_arr;
}

Matrix::Matrix(const Matrix &other) : Matrix(other.matrix_arr, other.matrix_rows, other.matrix_columns) {}

void Matrix::swap(Matrix &other) {
    std::swap(matrix_rows, other.matrix_rows);
    std::swap(matrix_columns, other.matrix_columns);
    std::swap(matrix_arr, other.matrix_arr);
}

Matrix::Matrix(double **arr, unsigned int rows, unsigned int columns) {
    matrix_rows = rows;
    matrix_columns = columns;
    matrix_arr = new double *[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned int j = 0; j < columns; ++j) {
            matrix_arr[i][j] = arr[i][j];
        }
    }
}

Matrix Matrix::ValueInited(double value, unsigned int rows, unsigned int columns) {
    auto mx = Matrix{};

    auto matrix_arr = new double *[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned int j = 0; j < columns; ++j) {
            matrix_arr[i][j] = value;
        }
    }

    mx.matrix_arr = matrix_arr;
    mx.matrix_rows = rows;
    mx.matrix_columns = columns;

    return mx;
}

template<unsigned int ROWS, unsigned int COLUMNS>
Matrix::Matrix(double **arr) : Matrix(arr, ROWS, COLUMNS) {}

template<unsigned int ROWS, unsigned int COLUMNS>
Matrix Matrix::ValueInited(double val) {
    return Matrix::ValueInited(val, ROWS, COLUMNS);
}

