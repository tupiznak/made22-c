#include "matrix_calc.h"

#include <utility>
#include "matrix_calc+private.h"

Matrix::Matrix() : impl_(new MatrixImpl()) {}

Matrix::Matrix(const Matrix &matrix) : impl_(new MatrixImpl()) {}

Matrix::~Matrix() {
    delete impl_;
}

void Matrix::swap(Matrix &other) {
    std::swap(field, other.field);
    std::swap(impl_, other.impl_);
}

Matrix::Matrix(std::vector<double> vector) : impl_(new MatrixImpl()) {
    impl_->SetItems(std::move(vector));
}

std::vector<double> &Matrix::GetData() {
    return impl_->GetItems();
}
