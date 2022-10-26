#include "matrix_calc+private.h"

void Matrix::MatrixImpl::SetItems(std::vector<double> const &data) {
    items = data;
}

std::vector<double> &Matrix::MatrixImpl::GetItems() {
    return items;
};