//
// Created by massonskyi on 25.10.24.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP


#include "abstractObject.hpp"
#include <vector>
#include "number.h"
API_MI_BEGIN
class Vector;
class Matrix final : public AbstractObject {
public API_METHODS:
    Matrix();
    explicit Matrix(const std::vector<Vector>& value);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix() override = default;

    [[nodiscard]]
    std::string hex() const override;

    [[nodiscard]]
    std::string dec() const override;

    [[nodiscard]]
    std::string oct() const override;

    [[nodiscard]]
    std::string bin() const override;

    // Operator overloads
    API_MI_ Matrix& operator=(const Matrix& other);
    API_MI_ Matrix& operator=(Matrix&& other) noexcept;

    API_MI_ bool operator==(const Matrix& other) const;
    API_MI_ bool operator!=(const Matrix& other) const;

    API_MI_ Matrix operator+(const Matrix& other) const;
    API_MI_ Matrix operator-(const Matrix& other) const;
    API_MI_ Matrix operator*(const Matrix& other) const;
    API_MI_ Matrix operator/(const Matrix& other) const;

    API_MI_ Matrix operator+(const Vector& other) const;
    API_MI_ Matrix operator-(const Vector& other) const;
    API_MI_ Matrix operator*(const Vector& other) const;
    API_MI_ Matrix operator/(const Vector& other) const;

    API_MI_ Matrix& operator+=(const Matrix& other);
    API_MI_ Matrix& operator-=(const Matrix& other);

    API_MI_ Matrix& operator+=(const Vector& other);
    API_MI_ Matrix& operator-=(const Vector& other);

    API_MI_ Matrix& operator++();    // Prefix increment
    API_MI_ Matrix operator++(int);  // Postfix increment
    API_MI_ Matrix& operator--();    // Prefix decrement
    API_MI_ Matrix operator--(int);  // Postfix decrement

    API_MI_ Vector operator[](int index) const;
    API_MI_ Vector& operator[](int index);

    [[nodiscard]]
    API_MI_ std::vector<std::vector<Number>>::size_type size() const;

    API_MI_ void append(const Vector& vector);
    API_MI_ void pop_back();
    API_MI_ void clear();
    API_MI_ void erase(int index);
    API_MI_ void insert(int index, const Vector& vector);
    API_MI_ void resize(int rows, int cols);
    API_MI_ void swap(Matrix& other) noexcept;

    API_MI_ std::vector<Vector>::iterator begin();
    API_MI_ std::vector<Vector>::iterator end();

    [[nodiscard]]
    API_MI_ std::vector<Vector>::const_iterator cbegin() const;

    [[nodiscard]]
    API_MI_ std::vector<Vector>::const_iterator cend() const;
    API_MI_ friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
private:
    std::vector<Vector> value_; // Change to store vectors directly
};

API_MI_END

#endif //MATRIX_HPP
