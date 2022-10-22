#ifndef MATRIX_CALC_MATRIX_CALC_PRIVATE_H
#define MATRIX_CALC_MATRIX_CALC_PRIVATE_H

#include <vector>

struct Matrix::MatrixImpl {
public:
    void SetItems(std::vector<double> data) {
        items = data;
    };

    std::vector<double> &GetItems() {
        return items;
    };

    void swap(MatrixImpl &other) {
        std::swap(items, other.items);
    };
private:
    std::vector<double> items;
};


#endif //MATRIX_CALC_MATRIX_CALC_PRIVATE_H
