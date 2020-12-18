#include <vector>
#include "matrix.hpp"


namespace LinearAlgebra {

    template<typename T>
    bool Matrix<T>::check_size(const Matrix &other) const {
        return _rows == other._rows && _cols == other._cols;
    }

    template<typename T>
    void swap(LinearAlgebra::Matrix<T> &a, LinearAlgebra::Matrix<T> &b) {
        std::swap(a._cols, b._cols);
        std::swap(a._rows, b._rows);
        std::swap(a._data, b._data);
    }

    template<typename T>
    Matrix<T>::Matrix() : _data(nullptr), _cols(0), _rows(0) {}

    template<typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols, const T &value) : _data(new T[rows * cols]), _cols(cols),
                                                                  _rows(rows) {
        std::fill_n(_data, rows * cols, value);
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix &other) : _data(new T[other._rows * other._cols]), _cols(other._cols),
                                             _rows(other._rows) {
        std::copy_n(other._data, _rows * _cols, _data);
    }

    template<typename T>
    Matrix<T>::~Matrix() {
        delete[] _data;
    }

    template<typename T>
    Matrix <T> &Matrix<T>::operator=(const Matrix &other) {
        if (&other != this) {
            Matrix tmp = Matrix(other);
            swap(*this, tmp);
        }
        return *this;
    }

    template<typename T>
    size_t Matrix<T>::rows() const {
        return _rows;
    }

    template<typename T>
    size_t Matrix<T>::cols() const {
        return _cols;
    }

    template<typename T>
    T *Matrix<T>::operator[](size_t row) {
        return _data + row * _cols;
    }

    template<typename T>
    const T *Matrix<T>::operator[](size_t row) const {
        return _data + row * _cols;
    }

    template<typename T>
    Matrix <T> &Matrix<T>::operator+=(const Matrix &other) {
        if (!check_size(other))
            throw MismatchMatrixSize();
        for (size_t i = 0; i < _rows * _cols; i++)
            _data[i] += other._data[i];
        return *this;
    }

    template<typename T>
    Matrix <T> Matrix<T>::operator+(const Matrix &other) const {
        return (Matrix(*this) += other);
    }

    template<typename T>
    Matrix <T> &Matrix<T>::operator-=(const Matrix &other) {
        if (!check_size(other))
            throw MismatchMatrixSize();
        for (size_t i = 0; i < _rows * _cols; i++)
            _data[i] -= other._data[i];
        return *this;
    }

    template<typename T>
    Matrix <T> Matrix<T>::operator-(const Matrix &other) const {
        return (Matrix(*this) -= other);
    }

    template<typename T>
    Matrix <T> Matrix<T>::operator*(const Matrix &other) const {
        if (_cols != other._rows)
            throw MismatchMatrixSize();
        Matrix res(_rows, other._cols);
        for (size_t i = 0; i < _rows; i++)
            for (size_t j = 0; j < other._cols; j++)
                for (size_t k = 0; k < _cols; k++)
                    res[i][j] += operator[](i)[k] * other[k][j];
        return res;
    }

    template<typename T>
    Matrix <T> &Matrix<T>::operator*=(const Matrix &other) {
        *this = *this * other;
        return *this;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, Matrix <T> &m) {
        size_t rows = 0, cols = 0;
        is >> rows >> cols;
        m = Matrix<T>(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i) {
            is >> m._data[i];
        }
        return is;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Matrix <T> &m) {
        os << m._rows << " " << m._cols << "\n";
        for (size_t i = 0; i < m._rows; ++i) {
            for (size_t j = 0; j < m._cols; ++j) {
                os << m[i][j];
                if (j < m._cols - 1)
                    os << " ";
            }
            os << "\n";
        }
        return os;
    }

    template<typename T>
    Matrix<T>::Matrix(std::initializer_list<T> diag) : Matrix(diag.size(), diag.size()) {
        for (size_t i = 0; i < _rows; i++)
            _data[i + i * _cols] = *(diag.begin() + i);
    }

    template<typename T>
    Matrix<T>::Matrix(std::vector<T> diag) : Matrix(diag.size(), diag.size()) {
        for (size_t i = 0; i < _rows; i++)
            _data[i + i * _cols] = diag[i];
    }

}