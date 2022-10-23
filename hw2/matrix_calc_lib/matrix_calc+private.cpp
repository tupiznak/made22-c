#include "matrix_calc+private.h"

void Matrix::MatrixImpl::SetItems(std::vector<double> const &data) {
    items = data;
}