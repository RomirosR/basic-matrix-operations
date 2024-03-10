#pragma once

#include <cstddef>
#include <vector>

template <class T>
class Matrix {
   private:
    std::vector<std::vector<T>> data_;

   public:
    explicit Matrix(int n);

    Matrix(int n, int m);

    Matrix(int n, int m, const T& value);

    explicit Matrix(const std::vector<std::vector<T>>& other);

    Matrix(const Matrix&);

    Matrix(Matrix&&) noexcept;

    Matrix& operator=(const Matrix&);

    Matrix& operator=(Matrix&&) noexcept;

    ~Matrix();

    std::size_t Rows() const;

    std::size_t Cols() const;

    bool Empty() const;

    const std::vector<std::vector<T>>& Data() const;

    Matrix& operator+=(const Matrix& other);

    Matrix operator+(const Matrix& other);
};

template <class T>
Matrix<T>::Matrix(int n) : data_(n, std::vector<T>(n)) {}

template <class T>
Matrix<T>::Matrix(int n, int m) : data_(n, std::vector<T>(m)) {}

template <class T>
Matrix<T>::Matrix(int n, int m, const T& value)
    : data_(n, std::vector<T>(m, value)) {}

template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& other) : data_(other) {}

template <class T>
Matrix<T>::Matrix(const Matrix& other) = default;

template <class T>
Matrix<T>::Matrix(Matrix&& other) noexcept = default;

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) = default;

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept = default;

template <class T>
Matrix<T>::~Matrix() = default;

template <class T>
std::size_t Matrix<T>::Rows() const {
    return data_.size();
}

template <class T>
std::size_t Matrix<T>::Cols() const {
    if (Rows() == 0) {
        return 0;
    }
    return data_[0].size();
}

template <class T>
bool Matrix<T>::Empty() const {
    return Rows() == 0 && Cols() == 0;
}

template <class T>
const std::vector<std::vector<T>>& Matrix<T>::Data() const {
    return data_;
}