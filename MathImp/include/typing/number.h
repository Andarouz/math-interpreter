//
// Created by massonskyi on 25.10.24.
//

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "variable.h"
API_MI_BEGIN

class Number final : public AbstractObject {
public API_METHODS:
    API_MI_ Number();
    API_MI_ explicit Number(Variable value);
    API_MI_ explicit Number(int value);
    API_MI_ explicit Number(float value);

    API_MI_ Number(const Number& other);
    API_MI_ Number(Number&& other) noexcept;
    API_MI_ ~Number() override = default;

    [[nodiscard]]
    API_MI_ std::string hex() const override;

    [[nodiscard]]
    API_MI_ std::string dec() const override;

    [[nodiscard]]
    API_MI_ std::string oct() const override;

    [[nodiscard]]
    API_MI_ std::string bin() const override;

    // Operator overloads
    API_MI_ Number& operator=(const Number& other);
    API_MI_ Number& operator=(Number&& other) noexcept;
    API_MI_ Number& operator=(Variable value);
    API_MI_ Number& operator=(int value);
    API_MI_ Number& operator=(float value);

    API_MI_ bool operator==(const Number& other) const;
    API_MI_ bool operator!=(const Number& other) const;
    API_MI_ Number operator+(const Number& other) const;
    API_MI_ Number operator-(const Number& other) const;
    API_MI_ Number operator*(const Number& other) const;
    API_MI_ Number operator/(const Number& other) const;

    API_MI_ Number& operator+=(const Number& other);
    API_MI_ Number& operator-=(const Number& other);
    API_MI_ Number& operator*=(const Number& other);
    API_MI_ Number& operator/=(const Number& other);

    API_MI_ Number& operator++();    // Prefix increment
    API_MI_ Number operator++(int);  // Postfix increment
    API_MI_ Number& operator--();    // Prefix decrement
    API_MI_ Number operator--(int);  // Postfix decrement
private API_VARIABLES:
    API_MI_ Variable value_;
};

API_MI_END

#endif //NUMBER_HPP
