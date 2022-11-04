#include "matrix.h"

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

double &Matrix::operator()(unsigned row, unsigned col) const {
    if (!IsInBounds(row, col)) {
        throw std::out_of_range("out of bounds");
    }
    return matrix_arr[row][col];
}

bool Matrix::operator==(const Matrix &other) const {
    if (!IsEqualShape(other)) {
        return false;
    }
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            if ((float) matrix_arr[i][j] != (float) other.matrix_arr[i][j]) {
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

Matrix Matrix::operator-(double val) {
    auto new_matrix = Matrix(*this);
    Matrix::add(new_matrix, -val);
    return {new_matrix};
}

Matrix &Matrix::operator+=(double val) {
    Matrix::add(*this, val);
    return *this;
}

Matrix &Matrix::operator-=(double val) {
    Matrix::add(*this, -val);
    return *this;
}

Matrix &Matrix::operator*=(double val) {
    Matrix::multiply(*this, val);
    return *this;
}

Matrix Matrix::operator*(double val) {
    auto new_matrix = Matrix(*this);
    Matrix::multiply(new_matrix, val);
    return {new_matrix};
}


bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}

