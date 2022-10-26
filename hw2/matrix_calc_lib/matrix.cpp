#include "matrix.h"

Matrix::~Matrix() {
    for (unsigned int i = 0; i < matrix_rows; ++i) {
        delete[] matrix_arr[i];
    }
    delete[]matrix_arr;
}

Matrix::Matrix(const Matrix &other) : Matrix(other.matrix_arr, other.matrix_rows, other.matrix_columns) {}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

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

double Matrix::operator()(unsigned int row, unsigned int col) const {
    if (row >= matrix_rows || col >= matrix_columns)
        throw std::out_of_range("out of bounds");
    return matrix_arr[row][col];
}

bool Matrix::operator==(const Matrix &other) const {
    if (matrix_rows != other.matrix_rows || matrix_columns != other.matrix_columns) {
        return false;
    }
    for (int i = 0; i < matrix_rows; ++i) {
        for (int j = 0; j < matrix_columns; ++j) {
            if (matrix_arr[i][j] != other.matrix_arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template<unsigned int ROWS, unsigned int COLUMNS>
Matrix::Matrix(double **arr) : Matrix(arr, ROWS, COLUMNS) {}

template<unsigned int ROWS, unsigned int COLUMNS>
Matrix Matrix::ValueInited(double val) {
    return Matrix::ValueInited(val, ROWS, COLUMNS);
}

