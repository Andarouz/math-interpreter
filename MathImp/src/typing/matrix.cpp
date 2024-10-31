#include "matrix.h"

#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "number.h"
#include "vector.h"
API_MI_NAMESPACE API_MI_ Matrix::Matrix()
    : value_() {}

API_MI_NAMESPACE API_MI_ Matrix::Matrix(const std::vector<Vector>& value)
    : value_(value) {}

API_MI_NAMESPACE API_MI_ Matrix::Matrix(const Matrix& other)
    : value_(other.value_) {}

API_MI_NAMESPACE API_MI_ Matrix::Matrix(Matrix&& other) noexcept
    : value_(std::move(other.value_)) {}

API_MI_BEGIN

API_MI_ std::string Matrix::hex() const {
    std::stringstream stream;
    for (const auto& row : value_) {
        stream << row.hex() << "\n";
    }
    return stream.str();
}

API_MI_ std::string Matrix::dec() const {
    std::stringstream stream;
    for (const auto& row : value_) {
        stream << row.dec() << "\n";
    }
    return stream.str();
}

API_MI_ std::string Matrix::oct() const {
    std::stringstream stream;
    for (const auto& row : value_) {
        stream << row.oct() << "\n";
    }
    return stream.str();
}

API_MI_ std::string Matrix::bin() const {
    std::stringstream stream;
    for (const auto& row : value_) {
        stream << row.bin() << "\n";
    }
    return stream.str();
}

API_MI_ Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    value_ = other.value_;
    return *this;
}

API_MI_ Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    value_ = std::move(other.value_);
    return *this;
}

API_MI_ bool Matrix::operator==(const Matrix& other) const {
    return value_ == other.value_;
}

API_MI_ bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

API_MI_ Matrix Matrix::operator+(const Matrix& other) const {
    if (size() != other.size()) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] += other[i]; // Using Vector's operator+
    }
    return result;
}

API_MI_ Matrix Matrix::operator-(const Matrix& other) const {
    if (size() != other.size()) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] -= other[i]; // Using Vector's operator-
    }
    return result;
}

API_MI_ Matrix Matrix::operator*(const Matrix& other) const {
    if (size() != other.size()) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] *= other[i]; // Using Vector's operator*
    }
    return result;
}

API_MI_ Matrix Matrix::operator/(const Matrix& other) const {
    if (size() != other.size()) {
        throw std::runtime_error("Matrix sizes are not equal");
    }
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] /= other[i]; // Using Vector's operator/
    }
    return result;
}

API_MI_ Matrix Matrix::operator+(const Vector& other) const {
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] += other; // Using Vector's operator+
    }
    return result;
}

API_MI_ Matrix Matrix::operator-(const Vector& other) const {
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] -= other; // Using Vector's operator-
    }
    return result;
}

API_MI_ Matrix Matrix::operator*(const Vector& other) const {
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] *= other; // Using Vector's operator*
    }
    return result;
}

API_MI_ Matrix Matrix::operator/(const Vector& other) const {
    Matrix result = *this; // Start with a copy of the current matrix
    for (std::size_t i = 0; i < size(); ++i) {
        result[i] /= other; // Using Vector's operator/
    }
    return result;
}

API_MI_ Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

API_MI_ Matrix& Matrix::operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
}

API_MI_ Matrix& Matrix::operator+=(const Vector& other) {
    *this = *this + other;
    return *this;
}

API_MI_ Matrix& Matrix::operator-=(const Vector& other) {
    *this = *this - other;
    return *this;
}

API_MI_ Matrix& Matrix::operator++() {
    for (auto& row : value_) {
        ++row; // Using Vector's operator++
    }
    return *this;
}

API_MI_ Matrix Matrix::operator++(int) {
    Matrix copy(*this);
    ++(*this);
    return copy;
}

API_MI_ Matrix& Matrix::operator--() {
    for (auto& row : value_) {
        --row; // Using Vector's operator--
    }
    return *this;
}

API_MI_ Matrix Matrix::operator--(int) {
    Matrix copy(*this);
    --(*this);
    return copy;
}



API_MI_ Vector Matrix::operator[](const int index) const {
    return value_[index];
}

API_MI_ Vector& Matrix::operator[](const int index) {
    return value_[index];
}

API_MI_ std::vector<std::vector<Number>>::size_type Matrix::size() const {
    return value_.size();
}

API_MI_ void Matrix::append(const Vector& vector) {
    value_.emplace_back(vector);
}

API_MI_ void Matrix::pop_back() {
    value_.pop_back();
}

API_MI_ void Matrix::clear() {
    value_.clear();
}

API_MI_ void Matrix::swap(Matrix& other) noexcept {
    value_.swap(other.value_);
}

API_MI_ void Matrix::erase(const int index) {
    value_.erase(value_.begin() + index);
}
API_MI_ void Matrix::insert(const int index, const Vector& vector) {
    value_.insert(value_.begin() + index, vector);
}

API_MI_ void Matrix::resize(const int rows, const int cols) {
    value_.resize(rows, Vector(cols));
}

API_MI_ std::vector<Vector>::iterator Matrix::begin() {
    return value_.begin();
}

API_MI_ std::vector<Vector>::iterator Matrix::end() {
    return value_.end();
}

API_MI_ std::vector<Vector>::const_iterator Matrix::cbegin() const {
    return value_.cbegin();
}

API_MI_ std::vector<Vector>::const_iterator Matrix::cend() const {
    return value_.cend();
}
API_MI_ std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "[";
    for (auto it = matrix.cbegin(); it != matrix.cend(); ++it) {
        os << *it;
        if (it != matrix.cend() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
API_MI_END
