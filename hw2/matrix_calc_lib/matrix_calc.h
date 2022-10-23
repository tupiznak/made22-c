#ifndef MATRIX_CALC_MATRIX_CALC_H
#define MATRIX_CALC_MATRIX_CALC_H

#include <algorithm>
#include <vector>

struct Matrix {
public:
    Matrix();

    Matrix(const Matrix &);

    explicit Matrix(std::vector<double> const &vector);

    Matrix &operator=(const Matrix &rhs);

    std::vector<double> &GetData();

    void swap(Matrix &other);

    double field{};

    ~Matrix();

private:
    class MatrixImpl;

    MatrixImpl *impl_;
};


#endif //MATRIX_CALC_MATRIX_CALC_H
