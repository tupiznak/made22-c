#ifndef MATRIX_CALC_MATRIX_CALC_H
#define MATRIX_CALC_MATRIX_CALC_H

#include <algorithm>
#include <vector>

struct Matrix {
public:
    Matrix();

    explicit Matrix(std::vector<double> vector);

    std::vector<double> &GetData();

    Matrix(const Matrix &matrix);

    Matrix &operator=(const Matrix &rhs) {
        if (this != &rhs) {
            Matrix(rhs).swap(*this);
        }
        return *this;
    }

    void swap(Matrix &other);

    double field{};

    ~Matrix();

private:
    class MatrixImpl;

    MatrixImpl *impl_;
};


#endif //MATRIX_CALC_MATRIX_CALC_H
