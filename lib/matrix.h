#pragma once

#include <cstddef>
#include <stdexcept>
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

    Matrix& operator-=(const Matrix& other);

    Matrix operator-(const Matrix& other);

    Matrix& operator*=(const Matrix& other);

    Matrix operator*(const Matrix& other);

    bool operator==(const Matrix& other) const;

    bool operator!=(const Matrix& other) const;

    Matrix operator*(const T& value) const;

    Matrix& operator*=(const T& value);
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

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    if (Rows() != other.Rows() || Cols() != other.Cols()) {
        throw std::invalid_argument("Dimensions don't match");
    }
    for (std::size_t i = 0; i < Rows(); i++) {
        for (std::size_t j = 0; j < Cols(); j++) {
            data_[i][j] += other.data_[i][j];
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    Matrix<T> temp(*this);
    temp += other;
    return temp;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    if (Rows() != other.Rows() || Cols() != other.Cols()) {
        throw std::invalid_argument("Dimensions don't match");
    }
    for (std::size_t i = 0; i < Rows(); i++) {
        for (std::size_t j = 0; j < Cols(); j++) {
            data_[i][j] -= other.data_[i][j];
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
    Matrix<T> temp(*this);
    temp -= other;
    return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    if (Cols() != other.Rows()) {
        throw std::invalid_argument("Dimensions don't match");
    }
    Matrix<T> temp(Rows(), other.Cols());
    for (std::size_t i = 0; i < Rows(); i++) {
        for (std::size_t j = 0; j < other.Cols(); j++) {
            for (std::size_t k = 0; k < Cols(); k++) {
                temp.data_[i][j] += data_[i][k] * other.data_[k][j];
            }
        }
    }
    return temp;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    return *this = (*this * other);
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    return data_ == other.data_;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
    return data_ != other.data_;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
    for (std::size_t i = 0; i < Rows(); i++) {
        for (std::size_t j = 0; j < Cols(); j++) {
            data_[i][j] *= value;
        }
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T& value) const {
    Matrix<T> temp(*this);
    temp *= value;
    return temp;
}

template <class T>
Matrix<T> operator*(const T& value, const Matrix<T>& mat) {
    return (mat * value);
}