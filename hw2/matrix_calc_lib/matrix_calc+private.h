#ifndef MATRIX_CALC_MATRIX_CALC_PRIVATE_H
#define MATRIX_CALC_MATRIX_CALC_PRIVATE_H

#include <utility>
#include <vector>
#include "matrix_calc.h"

struct Matrix::MatrixImpl {
public:
    void SetItems(std::vector<double> const &data);

    std::vector<double> &GetItems();

private:
    std::vector<double> items;
};


#endif //MATRIX_CALC_MATRIX_CALC_PRIVATE_H
