#ifndef MATRIX_CALC_MATRIX_H
#define MATRIX_CALC_MATRIX_H

#include <stdexcept>
#include <complex>

struct Matrix {
public:
    // constructors
    Matrix() : matrix_arr{}, matrix_rows{0}, matrix_columns{0} {};

    Matrix(double **arr, unsigned rows, unsigned columns);

    template<unsigned ROWS, unsigned COLS>
    static Matrix MatrixInit(const double (&arr)[ROWS][COLS]) {
        auto matrix = Matrix::EmptyInited(ROWS, COLS);
        for (unsigned i = 0; i < ROWS; ++i) {
            for (unsigned j = 0; j < COLS; ++j) {
                matrix.matrix_arr[i][j] = arr[i][j];
            }
        }
        return matrix;
    }

    template<unsigned ROWS>
    static double Test(const double (&)[ROWS]) { return 0; }

    Matrix(const Matrix &);

    ~Matrix();

    void swap(Matrix &);

    static Matrix ValueInited(double value, unsigned rows, unsigned columns);

    static Matrix EmptyInited(unsigned rows, unsigned columns);

    static Matrix VerticalStack(const Matrix &, const Matrix &);

    static Matrix HorizontalStack(const Matrix &, const Matrix &);

    // operators
    Matrix &operator=(const Matrix &);

    Matrix operator+(double);

    Matrix operator-(double);

    Matrix operator*(double);

    Matrix &operator+=(double);

    Matrix &operator-=(double);

    Matrix &operator*=(double);

    bool operator==(const Matrix &) const;

    bool operator!=(const Matrix &) const;

    double &operator()(unsigned row, unsigned col) const;

    Matrix operator()(const unsigned (&rows)[2], const unsigned (&cols)[2]) const;

    // functions
    bool IsEqualShape(const Matrix &) const;

    bool IsCanDot(const Matrix &) const;

    bool IsInBounds(unsigned row, unsigned col) const;

    static void add(const Matrix &, double value);

    static void multiply(const Matrix &, double value);

    Matrix diagonal();

    Matrix row(unsigned row);

    Matrix column(unsigned column);

    enum operation {
        sum, sub, mul
    };

    static Matrix ElementSum(const Matrix &, const Matrix &);

    static Matrix ElementMul(const Matrix &, const Matrix &);

    static Matrix ElementSub(const Matrix &, const Matrix &);

    static Matrix Dot(const Matrix &, const Matrix &);

    Matrix Transpose();

    double Determinant() const;

    Matrix Adjugate();

    Matrix Invertible();


private:
    static Matrix ElementOperation(const Matrix &, const Matrix &, operation);

    void ComputeElementInDot(const Matrix &, const Matrix &, unsigned processed_row, unsigned processed_col);

    static Matrix SortedByRows(const Matrix &);

    double **matrix_arr;
    unsigned matrix_rows, matrix_columns;
};


#endif  // MATRIX_CALC_MATRIX_H
