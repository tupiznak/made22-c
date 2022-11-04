#ifndef MATRIX_CALC_MATRIX_H
#define MATRIX_CALC_MATRIX_H

#include <stdexcept>
#include <complex>

struct Matrix {
public:
    // constructors
    Matrix() = default;

    Matrix(double **arr, unsigned rows, unsigned columns);

    Matrix(const Matrix &);

    ~Matrix();

    void swap(Matrix &);

    static Matrix ValueInited(double val, unsigned rows, unsigned columns);

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


#endif //MATRIX_CALC_MATRIX_H
