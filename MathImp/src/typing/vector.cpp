//
// Created by massonskyi on 25.10.24.
//

#include "vector.h"
#include "number.h"

#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>
API_MI_NAMESPACE API_MI_ Vector::Vector() : value_({}) {

}
API_MI_NAMESPACE API_MI_ Vector::Vector(std::vector<Number> value)
: value_(std::move(value)) {

}

API_MI_NAMESPACE API_MI_ Vector::Vector(const int value)
: value_(std::vector<Number>(value)) {

}

API_MI_NAMESPACE API_MI_ Vector::Vector(const Vector& other)
: value_(other.value_) {

}

API_MI_NAMESPACE API_MI_ Vector::Vector(Vector&& other) noexcept
: value_(std::move(other.value_)) {

}

API_MI_BEGIN

    API_MI_ std::string Vector::hex() const {
        std::stringstream stream;
        stream << std::hex;
        for (const auto& number : value_) {
            stream << number.hex() << " ";
        }
        return stream.str();
    }

    API_MI_ std::string Vector::dec() const {
        std::stringstream stream;
        for (const auto& number : value_) {
            stream << number.dec() << " ";
        }
        return stream.str();
    }

    API_MI_ std::string Vector::oct() const {
        std::stringstream stream;
        stream << std::oct;
        for (const auto& number : value_) {
            stream << number.oct() << " ";
        }
        return stream.str();
    }

    API_MI_ std::string Vector::bin() const {
        std::stringstream stream;
        stream << std::bitset<8>(size());
        return stream.str();
    }

    API_MI_ Vector& Vector::operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        value_ = other.value_;
        return *this;
    }

    API_MI_ Vector& Vector::operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        value_ = std::move(other.value_);
        return *this;
    }

    API_MI_ bool Vector::operator==(const Vector& other) const {
        return std::equal(
            cbegin(),
            value_.cend(),
            other.cbegin(),
            other.cend());
    }

    API_MI_ bool Vector::operator!=(const Vector& other) const {
        return !(*this == other);
    }

    API_MI_ Vector Vector::operator+(const Vector& other) const {
        if (value_.size() != other.value_.size()) {
            throw std::runtime_error("Vectors must be of the same size for addition");
        }
        std::vector<Number> result;
        result.reserve(value_.size());
        for (size_t i = 0; i < value_.size(); ++i) {
            result.push_back(value_[i] + other.value_[i]);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator+(const int other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i + other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator+(const float other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i + other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator-(const Vector& other) const {
        if (value_.size() != other.value_.size()) {
            throw std::runtime_error("Vectors must be of the same size for subtraction");
        }
        std::vector<Number> result;
        result.reserve(value_.size());
        for (size_t i = 0; i < value_.size(); ++i) {
            result.push_back(value_[i] - other.value_[i]);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator-(const int other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i - other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator-(const float other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i - other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator*(const Vector& other) const {
        if (value_.size() != other.value_.size()) {
            throw std::runtime_error("Vectors must be of the same size for multiplication");
        }
        std::vector<Number> result;
        result.reserve(value_.size());
        for (size_t i = 0; i < value_.size(); ++i) {
            result.push_back(value_[i] * other.value_[i]);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator*(const int other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i * other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator*(const float other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i * other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator/(const Vector& other) const {
        if (value_.size() != other.value_.size()) {
            throw std::runtime_error("Vectors must be of the same size for division");
        }
        std::vector<Number> result;
        result.reserve(value_.size());
        for (size_t i = 0; i < value_.size(); ++i) {
            result.push_back(value_[i] / other.value_[i]);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator/(const int other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i / other);
        }
        return Vector(result);
    }

    API_MI_ Vector Vector::operator/(const float other) const {
        std::vector<Number> result;
        result.reserve(value_.size());
        for (const auto & i : value_) {
            result.push_back(i / other);
        }
        return Vector(result);
    }

    API_MI_ Number Vector::operator[](const int index) const{
        return value_[index];
    }

    API_MI_ Number& Vector::operator[](const int index){
        return value_[index];
    }

    API_MI_ Vector& Vector::operator+=(const Vector& other) {
        *this = *this + other;
        return *this;
    }

    API_MI_ Vector& Vector::operator-=(const Vector& other) {
        *this = *this - other;
        return *this;
    }

    API_MI_ Vector& Vector::operator*=(const Vector& other) {
        *this = *this * other;
        return *this;
    }

    API_MI_ Vector& Vector::operator/=(const Vector& other) {
        *this = *this / other;
        return *this;
    }


    API_MI_ Vector& Vector::operator++() {
        for (auto& number : value_) {
            ++number;
        }
        return *this;
    }

    API_MI_ Vector Vector::operator++(int) {
        Vector copy(*this);
        ++(*this);
        return copy;
    }

    API_MI_ Vector& Vector::operator--() {
        for (auto& number : value_) {
            --number;
        }
        return *this;
    }

    API_MI_ Vector Vector::operator--(int) {
        Vector copy(*this);
        --(*this);
        return copy;
    }

    API_MI_ std::vector<Number>::size_type Vector::size() const {
        return value_.size();
    }

    API_MI_ void Vector::append(const Number& number) {
        value_.push_back(number);
    }

    API_MI_ void Vector::pop_back() {
        value_.pop_back();
    }

    API_MI_ void Vector::clear() {
        value_.clear();
    }

    API_MI_ void Vector::erase(const int index) {
        value_.erase(value_.begin() + index);
    }

    API_MI_ void Vector::insert(const int index, const Number& number) {
        value_.insert(value_.begin() + index, number);
    }

    API_MI_ void Vector::resize(const int size) {
        value_.resize(size);
    }

    API_MI_ void Vector::swap(Vector& other) noexcept {
        value_.swap(other.value_);
    }

    API_MI_ std::vector<Number>::iterator Vector::begin() {
        return value_.begin();
    }

    API_MI_ std::vector<Number>::iterator Vector::end() {
        return value_.end();
    }

    API_MI_ std::vector<Number>::const_iterator Vector::cbegin() const {
        return value_.cbegin();
    }

    API_MI_ std::vector<Number>::const_iterator Vector::cend() const {
        return value_.cend();
    }

API_MI_END