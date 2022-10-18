#include <gtest/gtest.h>

extern "C" {
#include "matrix_dot.h"
}

TEST(MatrixDot, ConstructorDestructorMatrix) {
    Matrix matrix = Matrix_zeros_constructor(10, 20);
    EXPECT_EQ(10, matrix.rows);
    EXPECT_EQ(20, matrix.columns);
    for (int r = 0; r < matrix.rows; ++r)
        for (int c = 0; c < matrix.columns; ++c)
            EXPECT_EQ(0, matrix.arr[r][c]);
    Matrix_destructor(matrix);
}

TEST(MatrixDot, IsCanDot) {
    {
        Matrix matrix_a = Matrix_zeros_constructor(10, 20);
        Matrix matrix_b = Matrix_zeros_constructor(2, 3);
        EXPECT_EQ(false, Matrix_is_can_dot(matrix_a, matrix_b));
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
    {
        Matrix matrix_a = Matrix_zeros_constructor(10, 20);
        Matrix matrix_b = Matrix_zeros_constructor(20, 3);
        EXPECT_EQ(true, Matrix_is_can_dot(matrix_a, matrix_b));
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
}


TEST(MatrixDot, ElementProcessing) {
    {
        Matrix matrix_a = Matrix_zeros_constructor(20, 10);
        Matrix matrix_b = Matrix_zeros_constructor(10, 4);
        Matrix matrix_result = Matrix_zeros_constructor(20, 4);
        for (int i = 0; i < 10; ++i) {
            matrix_a.arr[3][i] = i;
            matrix_b.arr[i][2] = i * 3;

            matrix_a.arr[0][i] = -i;
            matrix_b.arr[i][1] = i * 4;
        }
        {
            Operation result = Matrix_compute_new_element(matrix_a, matrix_b, matrix_result, 3, 2);
            EXPECT_EQ(true, result.success);
            EXPECT_EQ(855, matrix_result.arr[3][2]);
            EXPECT_EQ(0, matrix_result.arr[0][1]);
        }
        {
            Operation result = Matrix_compute_new_element(matrix_a, matrix_b, matrix_result, 0, 1);
            EXPECT_EQ(true, result.success);
            EXPECT_EQ(855, matrix_result.arr[3][2]);
            EXPECT_EQ(-1140, matrix_result.arr[0][1]);
        }
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
    {
        Matrix matrix_a = Matrix_zeros_constructor(20, 10);
        Matrix matrix_b = Matrix_zeros_constructor(10, 4);
        Matrix matrix_result = Matrix_empty_constructor(20, 4);
        Operation result = Matrix_compute_new_element(matrix_a, matrix_b, matrix_result, 30, 2);
        EXPECT_EQ(false, result.success);
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
    {
        Matrix matrix_a = Matrix_zeros_constructor(20, 10);
        Matrix matrix_b = Matrix_zeros_constructor(10, 4);
        Matrix matrix_result = Matrix_empty_constructor(20, 4);
        Operation result = Matrix_compute_new_element(matrix_a, matrix_b, matrix_result, 3, 20);
        EXPECT_EQ(false, result.success);
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
}


TEST(MatrixDot, BadOperation) {
    {
        Matrix matrix_a = Matrix_zeros_constructor(10, 20);
        Matrix matrix_b = Matrix_zeros_constructor(2, 3);
        Operation result = Matrix_dot(matrix_a, matrix_b);
        EXPECT_EQ(false, result.success);
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
    {
        Matrix matrix_a = Matrix_zeros_constructor(20, 10);
        Matrix matrix_b = Matrix_zeros_constructor(10, 4);
        matrix_a.rows = -1;
        Operation result = Matrix_dot(matrix_a, matrix_b);
        EXPECT_EQ(false, result.success);
        Matrix_destructor(matrix_a);
        Matrix_destructor(matrix_b);
    }
}

TEST(MatrixDot, Dot) {
    Matrix matrix_a = Matrix_empty_constructor(10, 3);
    Matrix matrix_b = Matrix_empty_constructor(3, 2);
    Matrix matrix_check = Matrix_empty_constructor(10, 2);
    for (int i = 0; i < matrix_a.rows; ++i) {
        for (int j = 0; j < matrix_a.columns; ++j) {
            matrix_a.arr[i][j] = i * matrix_a.columns + j;
        }
    } // a = np.array([i for i in range(10 * 3)]).reshape((10, 3))
    for (int i = 0; i < matrix_b.columns; ++i) {
        for (int j = 0; j < matrix_b.rows; ++j) {
            matrix_b.arr[j][i] = i * matrix_b.rows + j;
        }
    } //  b = np.array([i for i in range(3 * 2)]).reshape((2, 3)).T
    for (int i = 0; i < matrix_a.rows; ++i) {
        matrix_check.arr[i][0] = 5 + 9 * i;
        matrix_check.arr[i][1] = 14 + 36 * i;
    } //  np.dot(a, b)

    Operation result = Matrix_dot(matrix_a, matrix_b);
    EXPECT_EQ(true, result.success);
    EXPECT_EQ(true, Matrix_is_equal(*result.matrix, matrix_check));
    matrix_check.arr[0][0] = 10000;
    EXPECT_EQ(false, Matrix_is_equal(*result.matrix, matrix_check));
    matrix_check.arr[0][0] = result.matrix->arr[0][0];
    EXPECT_EQ(true, Matrix_is_equal(*result.matrix, matrix_check));
    matrix_check.columns = 10000;
    EXPECT_EQ(false, Matrix_is_equal(*result.matrix, matrix_check));
    Matrix_destructor(matrix_a);
    Matrix_destructor(matrix_b);
    Matrix_destructor(*result.matrix);
    free(result.matrix);
}

