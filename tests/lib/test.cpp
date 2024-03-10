#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include "lib/matrix.h"
#include <vector>
#include <iostream>

template <class T>
void Check(const Matrix<T>& actual, const std::vector<std::vector<int>>& expected) {
    REQUIRE(actual.Rows() == expected.size());
    for (size_t i = 0; i < actual.Rows(); i++) {
        REQUIRE(expected[i].size() == actual.Cols());
        for (size_t j = 0; j < actual.Cols(); j++) {
            std::cout << actual.Data()[i][j] << " " << expected[i][j] << "\n";
            if (actual.Data()[i][j] != expected[i][j]) {
                FAIL(actual.Data()[i][j] << " != " << expected[i][j]);
            }
        }
    }
}

TEST_CASE("Matrix has constructors") {
    std::vector<std::vector<int>> a{{1, 2}, {3, 4}};
    Matrix<int> mat1(a);
    Check(mat1, a);

    Matrix<int> mat2(3);
    Check(mat2, std::vector<std::vector<int>>(3, std::vector<int>(3)));

    Matrix<int> mat3(3, 4);
    Check(mat3, std::vector<std::vector<int>>(3, std::vector<int>(4)));

    Matrix<int> mat4(3, 4, 1);
    Check(mat4, std::vector<std::vector<int>>(3, std::vector<int>(4, 1)));

    auto mat5(mat1);
    Check(mat5, a);

    mat2 = std::move(mat1);
    REQUIRE(mat1.Empty());
    Check(mat2, a);

    auto mat6(std::move(mat2));
    REQUIRE(mat1.Empty());
    REQUIRE(mat2.Empty());
    Check(mat6, a);
}
