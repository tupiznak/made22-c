#ifndef MATRIX_CALC_VECTOR_H
#define MATRIX_CALC_VECTOR_H


#include "matrix.h"

class VectorRow : public Matrix {
public:
    VectorRow(double *arr, unsigned);

    double &operator()(unsigned) const;
};

class VectorCol : public Matrix {
public:
    VectorCol() = default;

    VectorCol(double *arr, unsigned);

    explicit VectorCol(const Matrix &);

    double &operator()(unsigned) const;

    VectorCol &operator=(const Matrix &);
};


#endif //MATRIX_CALC_VECTOR_H
