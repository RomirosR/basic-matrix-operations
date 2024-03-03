#pragma once

#include <vector>

template <typename T>
class Matrix {
   private:
    std::vector<std::vector<T>> data_;

   public:
    explicit Matrix(int n);

    Matrix(const Matrix&);

    Matrix(Matrix&&) noexcept;

    Matrix& operator=(const Matrix&);

    Matrix& operator=(Matrix&&) noexcept;

    ~Matrix();
};