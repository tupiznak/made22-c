#include <gtest/gtest.h>
#include "matrix_calc.h"

TEST(MatrixCalc, ConstructorDestructorMatrix) {
    auto row = std::vector<double>{3, 4, 5, 6, 4.9, 4, 4, 4, 42, 2, 23};
    row.push_back(3);
    std::vector<double> dupRow = row;
    auto matrix1 = new Matrix(row);
    row.clear();

    auto vecFromMatrix = matrix1->GetData();

    EXPECT_EQ(0, row.size());
    ASSERT_EQ(dupRow.size(), vecFromMatrix.size());

    for (size_t i = 0; i < dupRow.size(); ++i) {
        EXPECT_DOUBLE_EQ(dupRow[i], vecFromMatrix[i]);
    }

    Matrix matrix2;
    matrix2 = *matrix1;

    delete matrix1;
}