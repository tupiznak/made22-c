#include <gtest/gtest.h>
#include "matrix.h"

TEST(Matrix, ConstructorDestructorMatrix) {
    auto matrix0 = Matrix::ValueInited(0, 10, 20);
    EXPECT_EQ(0, matrix0(2, 3));
    ASSERT_THROW(matrix0(30, 20), std::out_of_range);

    auto matrix2 = Matrix::ValueInited(2, 10, 20);
    EXPECT_EQ(2, matrix2(6, 1));
    ASSERT_THROW(matrix2(30, 20), std::out_of_range);

    EXPECT_EQ(false, matrix0 == matrix2);
}