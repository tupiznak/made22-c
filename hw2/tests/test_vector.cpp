#include <gtest/gtest.h>
#include "vector.h"

TEST(Vector, ConstructorDestructorCompareVector) {
    auto arr = new double[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    auto vec_col = VectorCol(arr, 10);
    auto vec_row = VectorRow(arr, 10);
    EXPECT_EQ(true, vec_col.IsCanDot(vec_row));
    EXPECT_EQ(true, vec_row.IsCanDot(vec_col));
    EXPECT_EQ(false, vec_row.IsCanDot(vec_row));
    EXPECT_EQ(false, vec_col.IsCanDot(vec_col));
    vec_col += 4;
    vec_row -= 1;
    EXPECT_EQ(4, vec_col(0));
    EXPECT_EQ(6, vec_col(2));
    EXPECT_EQ(-1, vec_row(0));
    EXPECT_EQ(1, vec_row(2));
    Matrix::Dot(vec_col, vec_row);
    EXPECT_THROW(Matrix::Dot(vec_col, vec_col), std::logic_error);
    delete[] arr;
}
