#include "matrix.h"

bool Matrix::IsCanDot(const Matrix &b) const {
    return matrix_columns == b.matrix_rows;
}

void Matrix::ComputeElementInDot(const Matrix &a, const Matrix &b, unsigned processed_row, unsigned processed_col) {
    if (!IsInBounds(processed_row, processed_col)) {
        throw std::out_of_range("out of bounds");
    }

    double sum = 0;
    for (unsigned i = 0; i < a.matrix_columns; ++i) {
        sum += a.matrix_arr[processed_row][i] * b.matrix_arr[i][processed_col];
    }
    matrix_arr[processed_row][processed_col] = sum;
}

Matrix Matrix::Dot(const Matrix &a, const Matrix &b) {
    if (!a.IsCanDot(b)) {
        throw std::out_of_range("matrix A columns not equal matrix B rows");
    }

    auto result = Matrix::EmptyInited(a.matrix_rows, b.matrix_columns);
    for (unsigned i = 0; i < a.matrix_rows; ++i) {
        for (unsigned j = 0; j < b.matrix_columns; ++j) {
            result.ComputeElementInDot(a, b, i, j);
        }
    }
    return result;
}
