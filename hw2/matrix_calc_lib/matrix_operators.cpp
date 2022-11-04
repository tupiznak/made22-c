#include "matrix.h"

auto Matrix::operator=(const Matrix &other) -> Matrix & {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

auto Matrix::operator()(unsigned row, unsigned col) const -> double & {
    if (!IsInBounds(row, col)) {
        throw std::out_of_range("out of bounds");
    }
    return matrix_arr[row][col];
}

auto Matrix::operator==(const Matrix &other) const -> bool {
    if (!IsEqualShape(other)) {
        return false;
    }
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            if (static_cast<float>(matrix_arr[i][j]) != static_cast<float>(other.matrix_arr[i][j])) {
                return false;
            }
        }
    }
    return true;
}

auto Matrix::operator+(double val) -> Matrix {
    auto new_matrix = Matrix(*this);
    Matrix::add(new_matrix, val);
    return {new_matrix};
}

auto Matrix::operator-(double val) -> Matrix {
    auto new_matrix = Matrix(*this);
    Matrix::add(new_matrix, -val);
    return {new_matrix};
}

auto Matrix::operator+=(double val) -> Matrix & {
    Matrix::add(*this, val);
    return *this;
}

auto Matrix::operator-=(double val) -> Matrix & {
    Matrix::add(*this, -val);
    return *this;
}

auto Matrix::operator*=(double val) -> Matrix & {
    Matrix::multiply(*this, val);
    return *this;
}

auto Matrix::operator*(double val) -> Matrix {
    auto new_matrix = Matrix(*this);
    Matrix::multiply(new_matrix, val);
    return {new_matrix};
}


auto Matrix::operator!=(const Matrix &other) const -> bool {
    return !(*this == other);
}

auto Matrix::operator()(const unsigned int (&rows)[2], const unsigned int (&cols)[2]) const -> Matrix {
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