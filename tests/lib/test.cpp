#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

#include "lib/matrix.h"

template <class T>
void Check(const Matrix<T>& actual,
           const std::vector<std::vector<int>>& expected) {
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

TEST_CASE("Matrix addition") {
    Matrix<int> a({{1, 2}, {3, 4}});
    Matrix<int> b({{0, 1}, {1, 0}});

    Check(a + b, {{1, 3}, {4, 4}});

    a += b;
    Check(a, {{1, 3}, {4, 4}});

    a = Matrix<int>({{1, 2}, {3, 4}, {5, 6}});
    b = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    Check(a + b, {{2, 3}, {5, 6}, {8, 9}});

    a = Matrix<int>({{1, 2, 3}, {4, 5, 6}});
    b = Matrix<int>({{1, 1, 1}, {2, 2, 2}});
    Check(a + b, {{2, 3, 4}, {6, 7, 8}});

    a = Matrix<int>(2, 3);
    b = Matrix<int>(9, 12);
    REQUIRE_THROWS(a + b);
}

TEST_CASE("Matrix subtraction") {
    Matrix<int> a({{1, 2}, {3, 4}});
    Matrix<int> b({{0, 1}, {1, 0}});

    Check(a - b, {{1, 1}, {2, 4}});

    a -= b;
    Check(a, {{1, 1}, {2, 4}});

    a = Matrix<int>({{1, 2}, {3, 4}, {5, 6}});
    b = Matrix<int>({{1, 1}, {2, 2}, {3, 3}});
    Check(a - b, {{0, 1}, {1, 2}, {2, 3}});

    a = Matrix<int>({{1, 2, 3}, {4, 5, 6}});
    b = Matrix<int>({{1, 1, 1}, {2, 2, 2}});
    Check(a - b, {{0, 1, 2}, {2, 3, 4}});

    a = Matrix<int>(2, 3);
    b = Matrix<int>(9, 12);
    REQUIRE_THROWS(a - b);
}