//
// Created by massonskyi on 25.10.24.
//

#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <variant>

#include "AbstractObject.hpp"

API_MI_BEGIN
class Variable final : public AbstractObject{
public API_METHODS:
    enum class Type { INT, FLOAT, STRING };

    API_MI_ Variable();
    API_MI_ explicit Variable(int value);
    API_MI_ explicit Variable(float value);
    API_MI_ explicit Variable(std::string value);

    API_MI_ Variable(const Variable& other);
    API_MI_ Variable(Variable&& other) noexcept;

    API_MI_ ~Variable() override = default;

    [[nodiscard]]
    API_MI_ std::string hex() const override;

    [[nodiscard]]
    API_MI_ std::string dec() const override;

    [[nodiscard]]
    API_MI_ std::string oct() const override;

    [[nodiscard]]
    API_MI_ std::string bin() const override;

    // Operator overloads
    API_MI_ Variable& operator=(const Variable& other);
    API_MI_ Variable& operator=(Variable&& other) noexcept;
    API_MI_ Variable& operator=(int value);
    API_MI_ Variable& operator=(float value);
    API_MI_ Variable& operator=(const std::string& value);

    API_MI_ bool operator==(const Variable& other) const;
    API_MI_ bool operator!=(const Variable& other) const;
    API_MI_ Variable operator+(const Variable& other) const;
    API_MI_ Variable operator-(const Variable& other) const;
    API_MI_ Variable operator*(const Variable& other) const;
    API_MI_ Variable operator/(const Variable& other) const;

    API_MI_ Variable& operator+=(const Variable& other);
    API_MI_ Variable& operator-=(const Variable& other);
    API_MI_ Variable& operator*=(const Variable& other);
    API_MI_ Variable& operator/=(const Variable& other);
    API_MI_ Variable& operator++();    // Prefix increment
    API_MI_ Variable operator++(int);  // Postfix increment
    API_MI_ Variable& operator--();    // Prefix decrement
    API_MI_ Variable operator--(int);  // Postfix decrement

    [[nodiscard]]
    API_MI_ Type type() const;

    [[nodiscard]]
    API_MI_  int asInt() const;

    [[nodiscard]]
    API_MI_ float asFloat() const;

    [[nodiscard]]
    API_MI_ std::string asString() const;

    [[nodiscard]]
    API_MI_ int toInt() const;

    [[nodiscard]]
    API_MI_ float toFloat() const;

    [[nodiscard]]
    API_MI_ std::string toString() const;

    API_MI_ int toInt(bool& ok) const;
    API_MI_ float toFloat(bool& ok) const;
    API_MI_ std::string toString(bool& ok) const;

    [[nodiscard]]
    API_MI_ int toInt(int defaultValue) const;

    [[nodiscard]]
    API_MI_ float toFloat(float defaultValue) const;

    [[nodiscard]]
    API_MI_ std::string toString(const std::string& defaultValue) const;

    [[nodiscard]]
    API_MI_ int getInt() const;

    [[nodiscard]]
    API_MI_ float getFloat() const;

    [[nodiscard]]
    API_MI_ std::string getString() const;

private API_VARIABLES:
    std::variant<int, float, std::string> value_;
    Type type_;
};
API_MI_END


#endif //VARIABLE_HPP
