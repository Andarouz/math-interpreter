// rational.h
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include "AbstractObject.hpp"
API_MI_BEGIN

class Rational final : public AbstractObject {
    public API_METHODS:
        API_MI_ Rational();
    API_MI_ Rational(int numerator, int denominator);

    API_MI_ Rational(const Rational& other);
    API_MI_ Rational(Rational&& other) noexcept;

    API_MI_ ~Rational() override = default;

    [[nodiscard]]
    API_MI_ std::string hex() const override;

    [[nodiscard]]
    API_MI_ std::string dec() const override;

    [[nodiscard]]
    API_MI_ std::string oct() const override;

    [[nodiscard]]
    API_MI_ std::string bin() const override;

    // Operator overloads
    API_MI_ Rational& operator=(const Rational& other);
    API_MI_ Rational& operator=(Rational&& other) noexcept;

    API_MI_ bool operator==(const Rational& other) const;
    API_MI_ bool operator!=(const Rational& other) const;
    API_MI_ Rational operator+(const Rational& other) const;
    API_MI_ Rational operator-(const Rational& other) const;
    API_MI_ Rational operator*(const Rational& other) const;
    API_MI_ Rational operator/(const Rational& other) const;

    API_MI_ Rational& operator+=(const Rational& other);
    API_MI_ Rational& operator-=(const Rational& other);
    API_MI_ Rational& operator*=(const Rational& other);
    API_MI_ Rational& operator/=(const Rational& other);

    API_MI_ Rational& operator++();    // Prefix increment
    API_MI_ Rational operator++(int);  // Postfix increment
    API_MI_ Rational& operator--();    // Prefix decrement
    API_MI_ Rational operator--(int);  // Postfix decrement

    [[nodiscard]]
    API_MI_ int getNumerator() const;

    [[nodiscard]]
    API_MI_ int getDenominator() const;

    private API_VARIABLES:
        API_MI_ int numerator_;
    API_MI_ int denominator_;

    API_MI_ void reduce();
};

API_MI_END

#endif // RATIONAL_HPP