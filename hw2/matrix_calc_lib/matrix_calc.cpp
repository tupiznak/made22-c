#include <utility>

#include "matrix_calc.h"
#include "matrix_calc+private.h"

Matrix::Matrix() : impl_{new MatrixImpl} {}

Matrix::~Matrix() { delete impl_; }

Matrix::Matrix(const Matrix &other) : impl_{new MatrixImpl{*(other.impl_)}} {}

Matrix::Matrix(std::vector<double> const &vector) : impl_(new MatrixImpl) {
    impl_->SetItems(vector);
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        Matrix(other).swap(*this);
    }
    return *this;
}

void Matrix::swap(Matrix &other) {
    std::swap(field, other.field);
    std::swap(impl_, other.impl_);
}

std::vector<double> &Matrix::GetData() {
    return impl_->GetItems();
}
