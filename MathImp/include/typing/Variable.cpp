//
// Created by massonskyi on 25.10.24.
//

#include "Variable.h"

#include <stdexcept>

API_MI_NAMESPACE API_MI_ Variable::Variable()
    : value_(0), type_(Type::INT) {
}

API_MI_NAMESPACE API_MI_ Variable::Variable(int value)
    : value_(value), type_(Type::INT) {

}

API_MI_NAMESPACE API_MI_ Variable::Variable(float value)
    : value_(value), type_(Type::FLOAT) {

}

API_MI_NAMESPACE API_MI_ Variable::Variable(std::string value)
    : value_(std::move(value)), type_(Type::STRING) {

}

API_MI_NAMESPACE API_MI_ Variable::Variable(const Variable& other)
    : value_(other.value_), type_(other.type_) {

}

API_MI_NAMESPACE API_MI_ Variable::Variable(Variable&& other) noexcept
    : value_(std::move(other.value_)), type_(other.type_) {

}

API_MI_BEGIN

    API_MI_ std::string Variable::hex() const {
        switch (type_) {
            case Type::INT:
                return std::to_string(std::get<int>(value_));
            case Type::FLOAT:
                return std::to_string(std::get<float>(value_));
            case Type::STRING:
                return std::get<std::string>(value_);
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ std::string Variable::dec() const {
        switch (type_) {
            case Type::INT:
                return std::to_string(std::get<int>(value_));
            case Type::FLOAT:
                return std::to_string(std::get<float>(value_));
            case Type::STRING:
                return std::get<std::string>(value_);
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ std::string Variable::oct() const {
        switch (type_) {
            case Type::INT:
                return std::to_string(std::get<int>(value_));
            case Type::FLOAT:
                return std::to_string(std::get<float>(value_));
            case Type::STRING:
                return std::get<std::string>(value_);
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ std::string Variable::bin() const {
        switch (type_) {
            case Type::INT:
                return std::to_string(std::get<int>(value_));
            case Type::FLOAT:
                return std::to_string(std::get<float>(value_));
            case Type::STRING:
                return std::get<std::string>(value_);
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable::Type Variable::type() const {
        return type_;
    }

    API_MI_ int Variable::asInt() const {
        return std::get<int>(value_);
    }

    API_MI_ float Variable::asFloat() const {
        return std::get<float>(value_);
    }

    API_MI_ std::string Variable::asString() const {
        return std::get<std::string>(value_);
    }

    API_MI_ int Variable::toInt() const {
        return std::get<int>(value_);
    }

    API_MI_ float Variable::toFloat() const {
        return std::get<float>(value_);
    }

    API_MI_ std::string Variable::toString() const {
        return std::get<std::string>(value_);
    }

    API_MI_ int Variable::toInt(bool& ok) const {
        ok = true;
        return std::get<int>(value_);
    }

    API_MI_ float Variable::toFloat(bool& ok) const {
        ok = true;
        return std::get<float>(value_);
    }

    API_MI_ std::string Variable::toString(bool& ok) const {
        ok = true;
        return std::get<std::string>(value_);
    }

    API_MI_ int Variable::toInt(const int defaultValue) const {
        if (type_ == Type::INT) {
            return std::get<int>(value_);
        }
        return defaultValue;
    }

    API_MI_ float Variable::toFloat(const float defaultValue) const {
        if (type_ == Type::FLOAT) {
            return std::get<float>(value_);
        }
        return defaultValue;
    }

    API_MI_ std::string Variable::toString(const std::string& defaultValue) const {
        if (type_ == Type::STRING) {
            return std::get<std::string>(value_);
        }
        return defaultValue;
    }

    API_MI_ int Variable::getInt() const {
        return std::get<int>(value_);
    }

    API_MI_ float Variable::getFloat() const {
        return std::get<float>(value_);
    }

    API_MI_ std::string Variable::getString() const {
        return std::get<std::string>(value_);
    }

    API_MI_ Variable& Variable::operator=(const Variable& other) {
        if (this != &other) {
            value_ = other.value_;
            type_ = other.type_;
        }
        return *this;
    }

    API_MI_ Variable& Variable::operator=(Variable&& other) noexcept {
        if (this != &other) {
            value_ = std::move(other.value_);
            type_ = other.type_;
        }
        return *this;
    }

    API_MI_ Variable& Variable::operator=(int value) {
        value_ = value;
        type_ = Type::INT;
        return *this;
    }

    API_MI_ Variable& Variable::operator=(float value) {
        value_ = value;
        type_ = Type::FLOAT;
        return *this;
    }


    API_MI_ bool Variable::operator==(const Variable& other) const {
        if (type_ != other.type_) {
            return false;
        }
        switch (type_) {
            case Type::INT:
                return std::get<int>(value_) == std::get<int>(other.value_);
            case Type::FLOAT:
                return std::get<float>(value_) == std::get<float>(other.value_);
            case Type::STRING:
                return std::get<std::string>(value_) == std::get<std::string>(other.value_);
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ bool Variable::operator!=(const Variable& other) const {
        return !(*this == other);
    }

    API_MI_ Variable Variable::operator+(const Variable& other) const {
        switch (type_) {
            case Type::INT:
                return Variable(std::get<int>(value_) + other.asInt());
            case Type::FLOAT:
                return Variable(std::get<float>(value_) + other.asFloat());
            case Type::STRING:
                return Variable(std::get<std::string>(value_) + other.asString());
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable Variable::operator-(const Variable& other) const {
        switch (type_) {
            case Type::INT:
                return Variable(std::get<int>(value_) - other.asInt());
            case Type::FLOAT:
                return Variable(std::get<float>(value_) - other.asFloat());
            case Type::STRING:
                throw std::runtime_error("Invalid operation");
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable Variable::operator*(const Variable& other) const {
        switch (type_) {
            case Type::INT:
                return Variable(std::get<int>(value_) * other.asInt());
            case Type::FLOAT:
                return Variable(std::get<float>(value_) * other.asFloat());
            case Type::STRING:
                throw std::runtime_error("Invalid operation");
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable Variable::operator/(const Variable& other) const {
        switch (type_) {
            case Type::INT:
                return Variable(std::get<int>(value_) / other.asInt());
            case Type::FLOAT:
                return Variable(std::get<float>(value_) / other.asFloat());
            case Type::STRING:
                throw std::runtime_error("Invalid operation");
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable& Variable::operator+=(const Variable& other) {
        *this = *this + other;
        return *this;
    }

    API_MI_ Variable& Variable::operator-=(const Variable& other) {
        *this = *this - other;
        return *this;
    }

    API_MI_ Variable& Variable::operator++() {
        switch (type_) {
            case Type::INT:
                value_ = std::get<int>(value_) + 1;
                return *this;
            case Type::FLOAT:
                value_ = std::get<float>(value_) + 1;
                return *this;
            case Type::STRING:
                throw std::runtime_error("Invalid operation");
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable Variable::operator++(int) {
        Variable copy(*this);
        ++(*this);
        return copy;
    }

    API_MI_ Variable& Variable::operator--() {
        switch (type_) {
            case Type::INT:
                value_ = std::get<int>(value_) - 1;
                return *this;
            case Type::FLOAT:
                value_ = std::get<float>(value_) - 1;
                return *this;
            case Type::STRING:
                throw std::runtime_error("Invalid operation");
        }
        throw std::runtime_error("Invalid type");
    }

    API_MI_ Variable Variable::operator--(int) {
        Variable copy(*this);
        --(*this);
        return copy;
    }


API_MI_END
