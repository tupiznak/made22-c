#ifndef MATRIX_CALC_MATRIX_CALC_H
#define MATRIX_CALC_MATRIX_CALC_H

#include <algorithm>

struct Matrix {
public:
    Matrix() = default;

    Matrix(const Matrix &matrix);

    Matrix &operator=(const Matrix &rhs) {
        if (this != &rhs) {
            Matrix(rhs).swap(*this);
        }
        return *this;
    }

    void swap(Matrix &other) {
        std::swap(field, other.field);
        // impl_->swap(other.impl_);
    }

    double field{};

private:
//    class MatrixImpl;
//
//    MatrixImpl *impl_;
};

#endif //MATRIX_CALC_MATRIX_CALC_H
