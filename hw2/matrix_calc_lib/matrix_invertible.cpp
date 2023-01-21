#include "matrix.h"

auto Matrix::SortedByRows(const Matrix &orig_matrix) -> Matrix {
    Matrix matrix = orig_matrix;
    for (unsigned i = 0; i < matrix.matrix_rows; ++i) {
        unsigned max_non_zero_columns[2] = {0, i};
        for (unsigned j = i; j < matrix.matrix_rows; ++j) {
            unsigned k = 0;
            while (k < matrix.matrix_columns && static_cast<float>(orig_matrix.matrix_arr[j][k]) == 0) {
                k += 1;
            }
            k = matrix.matrix_columns - k;
            if (k > max_non_zero_columns[0]) {
                max_non_zero_columns[0] = k;
                max_non_zero_columns[1] = j;
            }
        }
        if (max_non_zero_columns[1] != i) {
            for (unsigned j = 0; j < matrix.matrix_columns; ++j) {
                auto tmp = matrix.matrix_arr[i][j];
                matrix.matrix_arr[i][j] = -matrix.matrix_arr[max_non_zero_columns[1]][j];
                matrix.matrix_arr[max_non_zero_columns[1]][j] = tmp;
            }
        }
    }
    return matrix;
}

auto Matrix::Determinant() const -> double {
    if (matrix_rows != matrix_columns) {
        throw std::range_error("rows and columns must be equal");
    }
    auto matrix = SortedByRows(*this);
    double determinant = 1;
    for (unsigned k = 0; k < matrix_rows - 1; ++k) {
        for (unsigned i = k + 1; i < matrix_rows; i++) {
            if (static_cast<float>(matrix.matrix_arr[k][k]) == 0) {
                continue;
            }
            double base = -matrix.matrix_arr[i][k] / matrix.matrix_arr[k][k];
            for (unsigned j = 0; j < matrix_rows; j++) {
                matrix.matrix_arr[i][j] += matrix.matrix_arr[k][j] * base;
            }
        }
    }
    for (unsigned i = 0; i < matrix_rows; i++) {
        determinant *= matrix.matrix_arr[i][i];
    }
    return determinant;
}

auto Matrix::Adjugate() -> Matrix {
    auto adjugate_matrix = EmptyInited(matrix_rows, matrix_columns);
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            auto imp_matrix = EmptyInited(matrix_rows - 1, matrix_columns - 1);
            for (unsigned k = 0, offset_k = 0; k < matrix_rows; ++k) {
                if (k == i) {
                    offset_k = 1;
                    continue;
                }
                for (unsigned l = 0, offset_l = 0; l < matrix_columns; ++l) {
                    if (l == j) {
                        offset_l = 1;
                        continue;
                    }
                    imp_matrix.matrix_arr[k - offset_k][l - offset_l] = matrix_arr[k][l];
                }
            }
            adjugate_matrix.matrix_arr[i][j] = imp_matrix.Determinant() * std::pow(-1, i + j);
        }
    }
    return adjugate_matrix;
}

auto Matrix::Invertible() -> Matrix {
    if (matrix_rows != matrix_columns) {
        throw std::range_error("cols and rows must be equal");
    }
    auto determinant = Determinant();
    if (determinant == 0) {
        throw std::logic_error("determinant must be non zero");
    }

    auto result = Adjugate().Transpose();
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            result.matrix_arr[i][j] /= determinant;
        }
    }
    return result;
}
