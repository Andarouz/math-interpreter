#include "rational.h"
#include <stdexcept>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <numeric>

API_MI_BEGIN

Rational::Rational() : numerator_{0}, denominator_{1} {}

Rational::Rational(const int numerator, const int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    numerator_ = numerator;
    denominator_ = denominator;
    reduce();
}

Rational::Rational(const Rational& other)
    : numerator_{other.numerator_}, denominator_{other.denominator_} {}

Rational::Rational(Rational&& other) noexcept
    : numerator_{other.numerator_}, denominator_{other.denominator_} {}

Rational& Rational::operator=(const Rational& other) {
    if (this != &other) {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
    }
    return *this;
}

Rational& Rational::operator=(Rational&& other) noexcept {
    if (this != &other) {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
    }
    return *this;
}

bool Rational::operator==(const Rational& other) const {
    return numerator_ == other.numerator_ && denominator_ == other.denominator_;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

Rational Rational::operator+(const Rational& other) const {
    const int num = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    const int denom = denominator_ * other.denominator_;
    return Rational{num, denom};
}

Rational Rational::operator-(const Rational& other) const {
    const int num = numerator_ * other.denominator_ - other.numerator_ * denominator_;
    const int denom = denominator_ * other.denominator_;
    return Rational{num, denom};
}

Rational Rational::operator*(const Rational& other) const {
    const int num = numerator_ * other.numerator_;
    const int denom = denominator_ * other.denominator_;
    return Rational{num, denom};
}

Rational Rational::operator/(const Rational& other) const {
    if (other.numerator_ == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    const int num = numerator_ * other.denominator_;
    const int denom = denominator_ * other.numerator_;
    return Rational{num, denom};
}

Rational& Rational::operator+=(const Rational& other) {
    *this = *this + other;
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    *this = *this - other;
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    *this = *this * other;
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    *this = *this / other;
    return *this;
}

Rational& Rational::operator++() {
    numerator_ += denominator_;
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp(*this);
    ++(*this);
    return temp;
}

Rational& Rational::operator--() {
    numerator_ -= denominator_;
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    --(*this);
    return temp;
}

int Rational::getNumerator() const {
    return numerator_;
}

int Rational::getDenominator() const {
    return denominator_;
}

std::string Rational::hex() const {
    std::stringstream stream;
    stream << std::hex << numerator_ << "/" << std::hex << denominator_;
    return stream.str();
}

std::string Rational::dec() const {
    return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

std::string Rational::oct() const {
    std::stringstream stream;
    stream << std::oct << numerator_ << "/" << std::oct << denominator_;
    return stream.str();
}

std::string Rational::bin() const {
    std::stringstream stream;
    stream << std::bitset<32>(numerator_) << "/" << std::bitset<32>(denominator_);
    return stream.str();
}

void Rational::reduce() {
    const int gcd = std::gcd(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

API_MI_END