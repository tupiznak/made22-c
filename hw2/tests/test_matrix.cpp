#include <gtest/gtest.h>
#include "matrix.h"

TEST(Matrix, ConstructorDestructorCompareMatrix) {
    auto matrix0 = Matrix::ValueInited(0, 10, 20);
    EXPECT_EQ(0, matrix0(2, 3));
    ASSERT_THROW(matrix0(30, 20), std::out_of_range);

    auto matrix2 = Matrix::ValueInited(2, 10, 20);
    EXPECT_EQ(2, matrix2(6, 1));
    ASSERT_THROW(matrix2(30, 20), std::out_of_range);

    EXPECT_EQ(false, matrix0 == matrix2);

    matrix0 = matrix0 + 1;
    EXPECT_EQ(1, matrix0(6, 1));
    matrix0 += 1;
    EXPECT_EQ(2, matrix0(6, 1));

    EXPECT_EQ(matrix0, matrix2);

    matrix0 += 10;
    EXPECT_NE(matrix0, matrix2);

    EXPECT_EQ(matrix0, matrix2 + 10);
    EXPECT_EQ(2, matrix2(6, 1));
}


TEST(Matrix, DiagRowColumn) {
    auto matrix0 = Matrix::ValueInited(8, 5, 3);
    matrix0(1, 1) = 2;
    auto matrix_check = Matrix::ValueInited(8, 1, 3);
    matrix_check(0, 1) = 2;

    EXPECT_EQ(matrix_check, matrix0.diagonal());
    EXPECT_EQ(Matrix::ValueInited(8, 1, 3), matrix0.row(2));
    EXPECT_EQ(Matrix::ValueInited(8, 5, 1), matrix0.column(0));
}

TEST(Matrix, ElementOperations) {
    EXPECT_EQ(Matrix::ValueInited(2, 5, 3),
              Matrix::ElementSum(Matrix::ValueInited(1, 5, 3),
                                 Matrix::ValueInited(1, 5, 3)));
    EXPECT_EQ(Matrix::ValueInited(5, 5, 3),
              Matrix::ElementSub(Matrix::ValueInited(6, 5, 3),
                                 Matrix::ValueInited(1, 5, 3)));
    EXPECT_EQ(Matrix::ValueInited(25, 5, 3),
              Matrix::ElementMul(Matrix::ValueInited(5, 5, 3),
                                 Matrix::ValueInited(5, 5, 3)));
    ASSERT_THROW(Matrix::ElementSub(Matrix::ValueInited(6, 2, 3),
                                    Matrix::ValueInited(1, 5, 3)), std::out_of_range);
}

TEST(Matrix, Dot) {
    EXPECT_EQ(Matrix::ValueInited(0, 5, 9),
              Matrix::Dot(Matrix::ValueInited(0, 5, 3),
                          Matrix::ValueInited(10, 3, 9)));
    ASSERT_THROW(Matrix::Dot(Matrix::ValueInited(0, 5, 6),
                             Matrix::ValueInited(10, 3, 9)), std::out_of_range);
}

TEST(Matrix, Transpose) {
    auto matrix0 = Matrix::ValueInited(8, 5, 3);
    matrix0(1, 1) = 2;
    matrix0(1, 2) = 20;
    auto matrix1 = Matrix::ValueInited(8, 3, 5);
    matrix1(1, 1) = 2;
    matrix1(2, 1) = 20;
    EXPECT_EQ(matrix0.Transpose(), matrix1);
}


TEST(Matrix, Determinant) {
    ASSERT_THROW(Matrix::ValueInited(0, 5, 6).Determinant(), std::range_error);
    EXPECT_EQ(0, Matrix::ValueInited(0, 5, 5).Determinant());
    EXPECT_EQ(0, Matrix::ValueInited(10, 5, 5).Determinant());
    {
        auto matrix = Matrix::EmptyInited(2, 2);
        matrix(0, 0) = 1;
        matrix(0, 1) = 2;
        matrix(1, 0) = 3;
        matrix(1, 1) = 4;
        EXPECT_DOUBLE_EQ(-2, matrix.Determinant());
    }
    {
        auto matrix = Matrix::EmptyInited(2, 2);
        matrix(0, 0) = 4;
        matrix(0, 1) = 2.4;
        matrix(1, 0) = 0;
        matrix(1, 1) = 3;
        EXPECT_DOUBLE_EQ(12, matrix.Determinant());
    }
    {
        auto matrix = Matrix::EmptyInited(2, 2);
        matrix(0, 0) = 5;
        matrix(0, 1) = 6;
        matrix(1, 0) = 8;
        matrix(1, 1) = 8;
        EXPECT_DOUBLE_EQ(-8, matrix.Determinant());
    }
    {
        auto matrix = Matrix::EmptyInited(2, 2);
        matrix(0, 0) = 4;
        matrix(0, 1) = 6;
        matrix(1, 0) = 7;
        matrix(1, 1) = 8;
        EXPECT_DOUBLE_EQ(-10, matrix.Determinant());
    }
    {
        auto matrix = Matrix::EmptyInited(2, 2);
        matrix(0, 0) = 0;
        matrix(0, 1) = 3;
        matrix(1, 0) = 82;
        matrix(1, 1) = 21.1;
        EXPECT_DOUBLE_EQ(-246, matrix.Determinant());
    }
}

TEST(Matrix, Adjugate) {
    auto matrix = Matrix::EmptyInited(3, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(0, 2) = 3;
    matrix(1, 0) = 4;
    matrix(1, 1) = 5;
    matrix(1, 2) = 6;
    matrix(2, 0) = 7;
    matrix(2, 1) = 8;
    matrix(2, 2) = 8;
    {
        auto matrix_check = Matrix::EmptyInited(3, 3);
        matrix_check(0, 0) = -8;
        matrix_check(0, 1) = 10;
        matrix_check(0, 2) = -3;
        matrix_check(1, 0) = 8;
        matrix_check(1, 1) = -13;
        matrix_check(1, 2) = 6;
        matrix_check(2, 0) = -3;
        matrix_check(2, 1) = 6;
        matrix_check(2, 2) = -3;
        for (unsigned i = 0; i < 3; ++i) {
            for (unsigned j = 0; j < 3; ++j) {
                EXPECT_DOUBLE_EQ(matrix_check(i, j), matrix.Adjugate()(i, j));
            }
        }
        EXPECT_EQ(matrix_check, matrix.Adjugate());
    }
}

TEST(Matrix, Invertible) {
    auto matrix = Matrix::EmptyInited(3, 3);
    matrix(0, 0) = 8;
    matrix(0, 1) = 4;
    matrix(0, 2) = 2.4;
    matrix(1, 0) = 9;
    matrix(1, 1) = 0;
    matrix(1, 2) = 3;
    matrix(2, 0) = 2;
    matrix(2, 1) = 82;
    matrix(2, 2) = 21.1;
    {
        auto matrix_check = Matrix::EmptyInited(3, 3);
        matrix_check(0, 0) = 205. / 777;
        matrix_check(0, 1) = -281. / 2331;
        matrix_check(0, 2) = -10. / 777;
        matrix_check(1, 0) = 613. / 3108;
        matrix_check(1, 1) = -410. / 2331;
        matrix_check(1, 2) = 2. / 777;
        matrix_check(2, 0) = -205. / 259;
        matrix_check(2, 1) = 180. / 259;
        matrix_check(2, 2) = 10. / 259;

        ASSERT_FLOAT_EQ(-4662. / 5, matrix.Determinant());
        for (unsigned i = 0; i < 3; ++i) {
            for (unsigned j = 0; j < 3; ++j) {
                EXPECT_FLOAT_EQ(matrix_check(i, j), matrix.Invertible()(i, j));
            }
        }
        EXPECT_EQ(matrix_check, matrix.Invertible());
    }
}
