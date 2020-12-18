#ifndef LINEAR_ALGEBRA_PROJECT_MATRIX_HPP
#define LINEAR_ALGEBRA_PROJECT_MATRIX_HPP

#include <ostream>
#include <istream>
#include <algorithm>
#include <vector>
#include "arithmetic_restriction.hpp"

namespace LinearAlgebra {

    class MismatchMatrixSize : public std::logic_error {
    public:
        MismatchMatrixSize() : logic_error("Mismatched matrix size") {}
    };

    template<typename T>
    class Matrix : ArithmeticRestriction<T> {
    private:
        bool check_size(const Matrix &other) const;

    protected:
        T *_data;
        size_t _cols{};
        size_t _rows{};

    public:
        Matrix();

        Matrix(size_t rows, size_t cols, const T &value = T());

        Matrix(std::initializer_list<T> diag);

        explicit Matrix(std::vector<T> diag);

        Matrix(const Matrix &other);

        ~Matrix();

        template<typename U>
        friend void swap(Matrix<U>& a, Matrix<U>& b);

        Matrix& operator=(const Matrix& other);

        [[nodiscard]] size_t rows() const;

        [[nodiscard]] size_t cols() const;

        T *operator[](size_t row);

        const T *operator[](size_t row) const;

        Matrix &operator+=(const Matrix &other);

        Matrix operator+(const Matrix &other) const;

        Matrix &operator-=(const Matrix &other);

        Matrix operator-(const Matrix &other) const;

        Matrix operator*(const Matrix &other) const;

        Matrix& operator*=(const Matrix &other);

        template<typename U>
        friend std::istream& operator>>(std::istream& is, Matrix<U>& m);

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);
    };

}

#include "matrix_impl.inl"

#endif //LINEAR_ALGEBRA_PROJECT_MATRIX_HPP
