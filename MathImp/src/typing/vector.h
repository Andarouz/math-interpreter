//
// Created by massonskyi on 25.10.24.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>
#include <vector>
#include "abstractObject.hpp"
#include "number.h"
API_MI_BEGIN

class Number;

class Vector final : public AbstractObject {
public API_METHODS:
    Vector();
    explicit Vector(std::vector<Number> value);
    explicit Vector(const int value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector() override = default;

    [[nodiscard]]
    std::string hex() const override;

    [[nodiscard]]
    std::string dec() const override;

    [[nodiscard]]
    std::string oct() const override;

    [[nodiscard]]
    std::string bin() const override;

    // Operator overloads
    API_MI_ Vector& operator=(const Vector& other);
    API_MI_ Vector& operator=(Vector&& other) noexcept;
    API_MI_ bool operator==(const Vector& other) const;
    API_MI_ bool operator!=(const Vector& other) const;
    API_MI_ Vector operator+(const Vector& other) const;
    API_MI_ Vector operator-(const Vector& other) const;
    API_MI_ Vector operator*(const Vector& other) const;
    API_MI_ Vector operator/(const Vector& other) const;

    API_MI_ Vector operator+(int other) const;
    API_MI_ Vector operator-(int other) const;
    API_MI_ Vector operator*(int other) const;
    API_MI_ Vector operator/(int other) const;

    API_MI_ Vector operator+(float other) const;
    API_MI_ Vector operator-(float other) const;
    API_MI_ Vector operator*(float other) const;
    API_MI_ Vector operator/(float other) const;

    API_MI_ Vector& operator+=(const Vector& other);
    API_MI_ Vector& operator-=(const Vector& other);
    API_MI_ Vector& operator*=(const Vector& other);
    API_MI_ Vector& operator/=(const Vector& other);

    API_MI_ Vector& operator+=(int other);
    API_MI_ Vector& operator-=(int other);
    API_MI_ Vector& operator*=(int other);
    API_MI_ Vector& operator/=(int other);

    API_MI_ Vector& operator+=(float other);
    API_MI_ Vector& operator-=(float other);
    API_MI_ Vector& operator*=(float other);
    API_MI_ Vector& operator/=(float other);

    API_MI_ Vector& operator++();    // Prefix increment
    API_MI_ Vector operator++(int);  // Postfix increment
    API_MI_ Vector& operator--();    // Prefix decrement
    API_MI_ Vector operator--(int);  // Postfix decrement


    API_MI_ Number operator[](int index) const;
    API_MI_ Number& operator[](int index);

    [[nodiscard]]
    API_MI_ std::vector<Number>::size_type size() const;

    API_MI_ void append(const Number& number);
    API_MI_ void pop_back();
    API_MI_ void clear();
    API_MI_ void erase(int index);
    API_MI_ void insert(int index, const Number& number);
    API_MI_ void resize(int size);
    API_MI_ void swap(Vector& other) noexcept;

    API_MI_ std::vector<Number>::iterator begin();
    API_MI_ std::vector<Number>::iterator end();

    [[nodiscard]]
    API_MI_ std::vector<Number>::const_iterator cbegin() const;

    [[nodiscard]]
    API_MI_ std::vector<Number>::const_iterator cend() const;

    API_MI_ friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "[";
        std::for_each(vector.cbegin(), vector.cend(), [&os, vector](const Number &number) {
            if(number == vector.cend()[-1])
                os << number;
            else
                os << number << ", ";
        });
        os << "]";
        return os;
    }
private API_VARIABLES:
    std::vector<Number> value_;
};

API_MI_END



#endif //VECTOR_HPP
