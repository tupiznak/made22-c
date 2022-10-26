#include "matrix.h"

Matrix Matrix::ElementOperation(const Matrix &a, const Matrix &b, Matrix::operation op) {
    if (!a.IsEqualShape(b)){
        throw std::out_of_range("matrix shapes not equal");
    }
    auto matrix = Matrix::EmptyInited(a.matrix_rows, a.matrix_columns);
    for (unsigned i = 0; i < matrix.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix.matrix_columns; ++j) {
            switch (op) {
                case sum:
                    matrix.matrix_arr[i][j] = a.matrix_arr[i][j] + b.matrix_arr[i][j];
                    break;
                case sub:
                    matrix.matrix_arr[i][j] = a.matrix_arr[i][j] - b.matrix_arr[i][j];
                    break;
                case mul:
                    matrix.matrix_arr[i][j] = a.matrix_arr[i][j] * b.matrix_arr[i][j];
                    break;
            }
        }
    }
    return matrix;
}

Matrix Matrix::ElementSum(const Matrix &a, const Matrix &b) {
    return Matrix::ElementOperation(a, b, sum);
}

Matrix Matrix::ElementMul(const Matrix &a, const Matrix &b) {
    return Matrix::ElementOperation(a, b, mul);
}

Matrix Matrix::ElementSub(const Matrix &a, const Matrix &b) {
    return Matrix::ElementOperation(a, b, sub);
}
