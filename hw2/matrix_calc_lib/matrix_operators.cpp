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

Matrix Matrix::operator()(const unsigned int (&rows)[2], const unsigned int (&cols)[2]) const {
    if (!(IsInBounds(rows[0], cols[0]) && IsInBounds(rows[1] - 1, cols[1] - 1))) {
        throw std::out_of_range("out of bounds in slice");
    }
    auto matrix = Matrix::EmptyInited(rows[1] - rows[0], cols[1] - cols[0]);
    for (unsigned i = rows[0]; i < rows[1]; ++i) {
        for (unsigned j = cols[0]; j < cols[1]; ++j) {
            matrix.matrix_arr[i - rows[0]][j - cols[0]] = matrix_arr[i][j];
        }
    }
    return matrix;
}