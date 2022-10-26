#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

struct Matrix {
public:
    Matrix() = default;

    template<unsigned int ROWS, unsigned int COLUMNS>
    explicit Matrix(double **arr);

    Matrix(double **arr, unsigned int rows, unsigned int columns);

    Matrix(const Matrix &);

    ~Matrix();

    Matrix &operator=(const Matrix &);

    Matrix operator+(double);

    Matrix &operator+=(double);

    bool operator==(const Matrix &) const;

    bool operator!=(const Matrix &) const;

    double operator()(unsigned row, unsigned col) const;

    template<unsigned int ROWS, unsigned int COLUMNS>
    static Matrix ValueInited(double val);

    static Matrix ValueInited(double val, unsigned int rows, unsigned int columns);
    static void add(const Matrix &, double value);

    void swap(Matrix &);


private:
    double **matrix_arr;
    unsigned int matrix_rows, matrix_columns;
};


#endif //MATRIX_H
