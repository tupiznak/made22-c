#include "matrix.h"

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

double Matrix::operator()(unsigned row, unsigned col) const {
    if (row >= matrix_rows || col >= matrix_columns)
        throw std::out_of_range("out of bounds");
    return matrix_arr[row][col];
}

bool Matrix::operator==(const Matrix &other) const {
    if (matrix_rows != other.matrix_rows || matrix_columns != other.matrix_columns) {
        return false;
    }
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            if (matrix_arr[i][j] != other.matrix_arr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::operator+(double val) {
    auto new_matrix = Matrix(*this);
    Matrix::add(new_matrix, val);
    return {new_matrix};
}

Matrix &Matrix::operator+=(double val) {
    Matrix::add(*this, val);
    return *this;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}
