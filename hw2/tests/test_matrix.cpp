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
