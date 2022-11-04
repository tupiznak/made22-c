#include "matrix.h"

auto Matrix::ElementOperation(const Matrix &a, const Matrix &b, Matrix::operation op) -> Matrix {
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

auto Matrix::ElementSum(const Matrix &a, const Matrix &b) -> Matrix {
    return Matrix::ElementOperation(a, b, sum);
}

auto Matrix::ElementMul(const Matrix &a, const Matrix &b) -> Matrix {
    return Matrix::ElementOperation(a, b, mul);
}

auto Matrix::ElementSub(const Matrix &a, const Matrix &b) -> Matrix {
    return Matrix::ElementOperation(a, b, sub);
}
