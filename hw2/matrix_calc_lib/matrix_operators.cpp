#include "matrix.h"

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
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
    for (unsigned int i = 0; i < matrix_rows; ++i) {
        for (unsigned int j = 0; j < matrix_columns; ++j) {
            if (matrix_arr[i][j] != other.matrix_arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix &Matrix::operator+(double val) {
    for (unsigned int i = 0; i < matrix_rows; ++i) {
        for (unsigned int j = 0; j < matrix_columns; ++j) {
            matrix_arr[i][j] += val;
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(double val) {
    return *this + val;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}