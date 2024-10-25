#include "number.h"
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>

API_MI_NAMESPACE API_MI_ Number::Number()
    : value_(0) {}

API_MI_NAMESPACE API_MI_ Number::Number(Variable value)
    : value_(std::move(value)) {}

API_MI_NAMESPACE API_MI_ Number::Number(const int value)
    : value_(value) {}

API_MI_NAMESPACE API_MI_ Number::Number(const float value)
    : value_(value) {}

API_MI_NAMESPACE API_MI_ Number::Number(const Number& other)
    : value_(other.value_) {}

API_MI_NAMESPACE API_MI_ Number::Number(Number&& other) noexcept
    : value_(std::move(other.value_)) {}

API_MI_BEGIN

API_MI_ std::string Number::hex() const {
    switch (value_.type()) {
        case Variable::Type::INT: {
            std::stringstream stream;
            stream << "0x" << std::hex << value_.getInt();
            return stream.str();
        }
        case Variable::Type::FLOAT: {
            std::stringstream stream;
            stream << std::hexfloat << value_.getFloat();
            return stream.str();
        }
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (char c : value_.getString()) {
                stream << "0x" <<  std::hex << static_cast<int>(c);
            }
            return stream.str();
        }
    }
    throw std::runtime_error("Invalid type");
}

API_MI_ std::string Number::dec() const {
    switch (value_.type()) {
        case Variable::Type::INT: {
            std::stringstream stream;
            stream << std::dec << value_.getInt();
            return stream.str();
        }
        case Variable::Type::FLOAT: {
            std::stringstream stream;
            stream << std::dec << value_.getFloat();
            return stream.str();
        }
        case Variable::Type::STRING: {
            return value_.getString();
        }
    }
    throw std::runtime_error("Invalid type");
}

API_MI_ std::string Number::oct() const {
    switch (value_.type()) {
        case Variable::Type::INT: {
            std::stringstream stream;
            stream << std::oct << value_.getInt();
            return stream.str();
        }
        case Variable::Type::FLOAT:
            throw std::runtime_error("Octal representation not supported for float");
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << std::oct << static_cast<int>(c);
            }
            return stream.str();
        }
    }
    throw std::runtime_error("Invalid type");
}

API_MI_ std::string Number::bin() const {
    switch (value_.type()) {
        case Variable::Type::INT: {
            std::stringstream stream;
            stream << std::bitset<8>(value_.getInt());
            return stream.str();
        }
        case Variable::Type::FLOAT:
            throw std::runtime_error("Binary representation not supported for float");
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << std::bitset<8>(c);
            }
            return stream.str();
        }
    }
    throw std::runtime_error("Invalid type");
}

API_MI_ Number& Number::operator=(const Number& other) {
    if (this != &other) {
        value_ = other.value_;
    }
    return *this;
}

API_MI_ Number& Number::operator=(Number&& other) noexcept {
    if (this != &other) {
        value_ = std::move(other.value_);
    }
    return *this;
}
API_MI_ Number& Number::operator=(Variable value) {
    value_ = std::move(value);
    return *this;
}

API_MI_ Number& Number::operator=(const int value) {
    value_ = value;
    return *this;
}

API_MI_ Number& Number::operator=(const float value) {
    value_ = value;
    return *this;
}


API_MI_ bool Number::operator==(const Number& other) const {
    if (value_.type() != other.value_.type()) {
        return false;
    }
    switch (value_.type()) {
        case Variable::Type::INT:
            return value_.getInt() == other.value_.getInt();
        case Variable::Type::FLOAT:
            return value_.getFloat() == other.value_.getFloat();
        default: {
            throw std::runtime_error("Unsupported type for comparison");
        }
    }
}

API_MI_ bool Number::operator!=(const Number& other) const {
    return !(*this == other);
}

API_MI_ Number Number::operator+(const Number& other) const {
    if (value_.type() == Variable::Type::INT && other.value_.type() == Variable::Type::INT) {
        return Number(value_.getInt() + other.value_.getInt());
    } else if (value_.type() == Variable::Type::FLOAT && other.value_.type() == Variable::Type::FLOAT) {
        return Number(value_.getFloat() + other.value_.getFloat());
    }
    throw std::runtime_error("Invalid type for addition");
}

API_MI_ Number Number::operator-(const Number& other) const {
    if (value_.type() == Variable::Type::INT && other.value_.type() == Variable::Type::INT) {
        return Number(value_.getInt() - other.value_.getInt());
    } else if (value_.type() == Variable::Type::FLOAT && other.value_.type() == Variable::Type::FLOAT) {
        return Number(value_.getFloat() - other.value_.getFloat());
    }
    throw std::runtime_error("Invalid type for subtraction");
}

API_MI_ Number Number::operator*(const Number& other) const {
    if (value_.type() == Variable::Type::INT && other.value_.type() == Variable::Type::INT) {
        return Number(value_.getInt() * other.value_.getInt());
    } else if (value_.type() == Variable::Type::FLOAT && other.value_.type() == Variable::Type::FLOAT) {
        return Number(value_.getFloat() * other.value_.getFloat());
    }
    throw std::runtime_error("Invalid type for multiplication");
}

API_MI_ Number Number::operator/(const Number& other) const {
    if (value_.type() == Variable::Type::INT && other.value_.type() == Variable::Type::INT) {
        if (other.value_.getInt() == 0) {
            throw std::runtime_error("Division by zero");
        }
        return Number(value_.getInt() / other.value_.getInt());
    } else if (value_.type() == Variable::Type::FLOAT && other.value_.type() == Variable::Type::FLOAT) {
        if (other.value_.getFloat() == 0.0f) {
            throw std::runtime_error("Division by zero");
        }
        return Number(value_.getFloat() / other.value_.getFloat());
    }
    throw std::runtime_error("Invalid type for division");
}

API_MI_ Number& Number::operator+=(const Number& other) {
    *this = *this + other;
    return *this;
}

API_MI_ Number& Number::operator-=(const Number& other) {
    *this = *this - other;
    return *this;
}

API_MI_ Number& Number::operator++() {
    switch (value_.type()) {
        case Variable::Type::INT:

            value_ = value_.getInt() + 1;
            return *this;
        case Variable::Type::FLOAT:
            value_ = value_.getFloat() + 1.0f;
            return *this;
        default:
            throw std::runtime_error("Invalid type for increment");
    }
}

API_MI_ Number Number::operator++(int) {
    Number temp(*this);
    ++(*this);
    return temp;
}

API_MI_ Number& Number::operator--() {
    switch (value_.type()) {
        case Variable::Type::INT:
            value_ = value_.getInt() - 1;
            return *this;
        case Variable::Type::FLOAT:
            value_ = value_.getFloat() - 1.0f;
            return *this;
        default:
            throw std::runtime_error("Invalid type for increment");
    }
}

API_MI_ Number Number::operator--(int) {
    Number temp(*this);
    --(*this);
    return temp;
}

API_MI_END
