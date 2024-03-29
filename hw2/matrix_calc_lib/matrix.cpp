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

Matrix::Matrix(double **arr, unsigned rows, unsigned columns)
        : matrix_rows(rows), matrix_columns(columns), matrix_arr(new double *[rows]) {
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned j = 0; j < columns; ++j) {
            matrix_arr[i][j] = arr[i][j];
        }
    }
}

auto Matrix::ValueInited(double value, unsigned rows, unsigned columns) -> Matrix {
    auto matrix = Matrix{};

    auto *matrix_arr = new double *[rows];
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
        for (unsigned j = 0; j < columns; ++j) {
            matrix_arr[i][j] = value;
        }
    }

    matrix.matrix_arr = matrix_arr;
    matrix.matrix_rows = rows;
    matrix.matrix_columns = columns;

    return matrix;
}

auto Matrix::EmptyInited(unsigned rows, unsigned columns) -> Matrix {
    auto matrix = Matrix{};

    auto *matrix_arr = new double *[rows];
    for (unsigned i = 0; i < rows; ++i) {
        matrix_arr[i] = new double[columns];
    }

    matrix.matrix_arr = matrix_arr;
    matrix.matrix_rows = rows;
    matrix.matrix_columns = columns;

    return matrix;
}


void Matrix::add(const Matrix &matrix, double value) {
    for (unsigned i = 0; i < matrix.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix.matrix_columns; ++j) {
            matrix.matrix_arr[i][j] += value;
        }
    }
}

void Matrix::multiply(const Matrix &matrix, double value) {
    for (unsigned i = 0; i < matrix.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix.matrix_columns; ++j) {
            matrix.matrix_arr[i][j] *= value;
        }
    }
}

auto Matrix::diagonal() -> Matrix {
    auto diag_len = std::min(matrix_rows, matrix_columns);
    auto vector = Matrix::EmptyInited(1, diag_len);
    for (unsigned i = 0; i < diag_len; ++i) {
        vector.matrix_arr[0][i] = matrix_arr[i][i];
    }
    return vector;
}

auto Matrix::row(unsigned row) -> Matrix {
    auto vector = Matrix::EmptyInited(1, matrix_columns);
    for (unsigned i = 0; i < matrix_columns; ++i) {
        vector.matrix_arr[0][i] = matrix_arr[row][i];
    }
    return vector;
}

auto Matrix::column(unsigned int column) -> Matrix {
    auto vector = Matrix::EmptyInited(matrix_rows, 1);
    for (unsigned i = 0; i < matrix_rows; ++i) {
        vector.matrix_arr[i][0] = matrix_arr[i][column];
    }
    return vector;
}

auto Matrix::IsEqualShape(const Matrix &other) const -> bool {
    return !(matrix_rows != other.matrix_rows || matrix_columns != other.matrix_columns);
}

auto Matrix::IsInBounds(unsigned row, unsigned col) const -> bool {
    return !(row >= matrix_rows || col >= matrix_columns);
}

auto Matrix::Transpose() -> Matrix {
    auto matrix = Matrix::EmptyInited(matrix_columns, matrix_rows);
    for (unsigned i = 0; i < matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_columns; ++j) {
            matrix.matrix_arr[j][i] = matrix_arr[i][j];
        }
    }
    return matrix;
}


auto Matrix::VerticalStack(const Matrix &matrix_a, const Matrix &matrix_b) -> Matrix {
    if (matrix_a.matrix_columns != matrix_b.matrix_columns) {
        throw std::range_error("vertical stacked elements must have equal columns length");
    }
    auto matrix = Matrix::EmptyInited(matrix_a.matrix_rows + matrix_b.matrix_rows, matrix_a.matrix_columns);
    for (unsigned i = 0; i < matrix_a.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_a.matrix_columns; ++j) {
            matrix.matrix_arr[i][j] = matrix_a.matrix_arr[i][j];
        }
    }
    for (unsigned i = 0; i < matrix_b.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_a.matrix_columns; ++j) {
            matrix.matrix_arr[i + matrix_a.matrix_rows][j] = matrix_b.matrix_arr[i][j];
        }
    }
    return matrix;
}

auto Matrix::HorizontalStack(const Matrix &matrix_a, const Matrix &matrix_b) -> Matrix {
    if (matrix_a.matrix_rows != matrix_b.matrix_rows) {
        throw std::range_error("vertical stacked elements must have equal rows length");
    }
    auto matrix = Matrix::EmptyInited(matrix_a.matrix_rows, matrix_a.matrix_columns + matrix_b.matrix_columns);

    for (unsigned i = 0; i < matrix_a.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_a.matrix_columns; ++j) {
            matrix.matrix_arr[i][j] = matrix_a.matrix_arr[i][j];
        }
    }
    for (unsigned i = 0; i < matrix_b.matrix_rows; ++i) {
        for (unsigned j = 0; j < matrix_a.matrix_columns; ++j) {
            matrix.matrix_arr[i][j + matrix_a.matrix_columns] = matrix_b.matrix_arr[i][j];
        }
    }
    return matrix;
}
