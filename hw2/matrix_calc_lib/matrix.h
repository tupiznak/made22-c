#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

struct Matrix {
public:
    // constructors
    Matrix() = default;

    template<unsigned ROWS, unsigned COLUMNS>
    explicit Matrix(double **arr);

    Matrix(double **arr, unsigned rows, unsigned columns);

    Matrix(const Matrix &);

    ~Matrix();

    void swap(Matrix &);

    template<unsigned ROWS, unsigned COLUMNS>
    static Matrix ValueInited(double val);

    static Matrix ValueInited(double val, unsigned rows, unsigned columns);

    static Matrix EmptyInited(unsigned rows, unsigned columns);

    // operators
    Matrix &operator=(const Matrix &);

    Matrix operator+(double);

    Matrix &operator+=(double);

    bool operator==(const Matrix &) const;

    bool operator!=(const Matrix &) const;

    double &operator()(unsigned row, unsigned col) const;

    // functions
    bool IsEqualShape(const Matrix &) const;

    static void add(const Matrix &, double value);

    Matrix diagonal();

    Matrix row(unsigned row);

    Matrix column(unsigned column);

    enum operation {
        sum, sub, mul
    };

    static Matrix ElementOperation(const Matrix &, const Matrix &, operation);

    static Matrix ElementSum(const Matrix &, const Matrix &);

    static Matrix ElementMul(const Matrix &, const Matrix &);

    static Matrix ElementSub(const Matrix &, const Matrix &);


private:
    double **matrix_arr;
    unsigned matrix_rows, matrix_columns;
};


#endif //MATRIX_H
