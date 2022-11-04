#include "vector.h"

VectorRow::VectorRow(double *arr, unsigned row_len) : Matrix{&arr, 1, row_len} {}

auto VectorRow::operator()(unsigned int col) const -> double & {
    return Matrix::operator()(0, col);
}

VectorCol::VectorCol(double *arr, unsigned col_len) : Matrix{&arr, 1, col_len} {
    *this = Transpose();
}

auto VectorCol::operator=(const Matrix &other) -> VectorCol & {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

auto VectorCol::operator()(unsigned int row) const -> double & {
    return Matrix::operator()(row, 0);
}

VectorCol::VectorCol(const Matrix &matrix)  {
    try {
        matrix(0, 1);
    } catch (const std::out_of_range &e) {
        *this = matrix;
        return;
    }
    throw std::logic_error("can not convert matrix to column with more than one columns");
}

