#include "matrix.h"

Matrix::~Matrix() {
    for (unsigned i = 0; i < matrix_rows; ++i) {
        delete[] matrix_arr[i];
    }
    delete[]matrix_arr;
}

Matrix::Matrix(const Matrix &other) : Matrix(other.matrix_arr, other.matrix_rows, other.matrix_columns) {}

void Matrix::swap(Matrix &other) {
    std::swap(matrix_rows, other.matrix_rows);
    std::swap(matrix_columns, other.matrix_columns);
    std::swap(matrix_arr, other.matrix_arr);
}

Matrix::Matrix(double **arr, unsigned rows, unsigned columns) {
    matrix_rows = rows;
    matrix_columns = columns;
    matrix_arr = new double *[rows];
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned j = 0; j < columns; ++j) {
            matrix_arr[i][j] = arr[i][j];
        }
    }
}

Matrix Matrix::ValueInited(double value, unsigned rows, unsigned columns) {
    auto mx = Matrix{};

    auto matrix_arr = new double *[rows];
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned j = 0; j < columns; ++j) {
            matrix_arr[i][j] = value;
        }
    }

    mx.matrix_arr = matrix_arr;
    mx.matrix_rows = rows;
    mx.matrix_columns = columns;

    return mx;
}

Matrix Matrix::EmptyInited(unsigned int rows, unsigned int columns) {
    auto mx = Matrix{};

    auto matrix_arr = new double *[rows];
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
    }

    mx.matrix_arr = matrix_arr;
    mx.matrix_rows = rows;
    mx.matrix_columns = columns;

    return mx;
}


template<unsigned ROWS, unsigned COLUMNS>
Matrix::Matrix(double **arr) : Matrix(arr, ROWS, COLUMNS) {}

template<unsigned ROWS, unsigned COLUMNS>
Matrix Matrix::ValueInited(double val) {
    return Matrix::ValueInited(val, ROWS, COLUMNS);
}

void Matrix::add(const Matrix &matrix, double value) {
    for (unsigned i = 0; i < matrix.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix.matrix_columns; ++j) {
            matrix.matrix_arr[i][j] += value;
        }
    }
}

Matrix Matrix::diagonal() {
    auto diag_len = std::min(matrix_rows, matrix_columns);
    auto vector = Matrix::EmptyInited(1, diag_len);
    for (unsigned i = 0; i < diag_len; ++i) {
        vector.matrix_arr[0][i] = matrix_arr[i][i];
    }
    return vector;
}

Matrix Matrix::row(unsigned row) {
    auto vector = Matrix::EmptyInited(1, matrix_columns);
    for (unsigned i = 0; i < matrix_columns; ++i) {
        vector.matrix_arr[0][i] = matrix_arr[row][i];
    }
    return vector;
}

Matrix Matrix::column(unsigned int column) {
    auto vector = Matrix::EmptyInited(matrix_rows, 1);
    for (unsigned i = 0; i < matrix_rows; ++i) {
        vector.matrix_arr[i][0] = matrix_arr[i][column];
    }
    return vector;
}

bool Matrix::IsEqualShape(const Matrix &other) const {
    if (matrix_rows != other.matrix_rows || matrix_columns != other.matrix_columns) {
        return false;
    }
    return true;
}

bool Matrix::IsInBounds(unsigned row, unsigned col) const {
    if (row >= matrix_rows || col >= matrix_columns) {
        return false;
    }
    return true;
}

Matrix Matrix::Transpose() {
    auto matrix = Matrix::EmptyInited(matrix_columns, matrix_rows);
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            matrix.matrix_arr[j][i] = matrix_arr[i][j];
        }
    }
    return matrix;
}

double Matrix::Determinant() {
    if (matrix_rows != matrix_columns) {
        throw std::range_error("rows and columns must be equal");
    }
    double determinant = 1;
    for (unsigned k = 0; k < matrix_rows - 1; ++k) {
        for (unsigned i = k + 1; i < matrix_rows; i++) {
            if (matrix_arr[k][k] == 0) {
                continue;
            }
            double base = -matrix_arr[i][k] / matrix_arr[k][k];
            for (unsigned j = 0; j < matrix_rows; j++) {
                matrix_arr[i][j] += matrix_arr[k][j] * base;
            }
        }
    }
    for (unsigned i = 0; i < matrix_rows; i++) {
        determinant *= matrix_arr[i][i];
    }
    return determinant;
}

double Matrix::Invertible() {
    if (matrix_rows != matrix_columns) {
        throw std::range_error("cols and rows must be equal");
    }
    auto determinant = Determinant();
    if (determinant == 0) {
        throw std::logic_error("determinant must be non zero");
    }

}

Matrix Matrix::Adjugate() {
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
