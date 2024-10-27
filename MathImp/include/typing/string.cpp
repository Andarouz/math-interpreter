//
// Created by gavri on 27.10.2024.
//
#include "string.h"

#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>

API_MI_NAMESPACE String::String()
    : value_("") {}

API_MI_NAMESPACE String::String(Variable value)
    : value_(std::move(value)) {}

API_MI_NAMESPACE String::String(const std::string& value)
    : value_(value) {}

API_MI_NAMESPACE String::String(const char* value)
    : value_(value) {}

API_MI_NAMESPACE String::String(const String& other)
    : value_(other.value_) {}

API_MI_NAMESPACE String::String(String&& other) noexcept
    : value_(std::move(other.value_)) {}

API_MI_BEGIN

API_MI_ std::string String::hex() const {
    switch (value_.type()) {
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << "0x" << std::hex << static_cast<int>(c);
            }
            return stream.str();
        }
        default: {
            throw std::runtime_error("Invalid type");
        }
    }
}

API_MI_ std::string String::dec() const {
    switch (value_.type()) {
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << std::dec << static_cast<int>(c);
            }
            return stream.str();
        }
        default: {
            throw std::runtime_error("Invalid type");
        }
    }
}

API_MI_ std::string String::oct() const {
    switch (value_.type()) {
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << std::oct << static_cast<int>(c);
            }
            return stream.str();
        }
        default: {
            throw std::runtime_error("Invalid type");
        }
    }
}

API_MI_ std::string String::bin() const {
    switch (value_.type()) {
        case Variable::Type::STRING: {
            std::stringstream stream;
            for (const char c : value_.getString()) {
                stream << std::bitset<8>(c);
            }
            return stream.str();
        }
        default: {
            throw std::runtime_error("Invalid type");
        }
    }
}

API_MI_ String& String::operator=(const String& other) {
    if (this != &other) {
        value_ = other.value_;
    }
    return *this;
}

API_MI_ String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        value_ = std::move(other.value_);
    }
    return *this;
}

API_MI_ String& String::operator=(Variable value) {
    value_ = std::move(value);
    return *this;
}

API_MI_ String& String::operator=(const std::string& value) {
    value_ = value;
    return *this;
}

API_MI_ String& String::operator=(const char* value) {
    value_ = value;
    return *this;
}

API_MI_ bool String::operator==(const String& other) const {
    return value_ == other.value_;
}

API_MI_ bool String::operator!=(const String& other) const {
    return !(*this == other);
}

API_MI_ String String::operator+(const String& other) const {
    return String(value_.getString() + other.value_.getString());
}

API_MI_ String String::operator-(const String& other) const {
    throw std::runtime_error("Subtraction is not supported for strings");
}

API_MI_ String String::operator*(const String& other) const {
    throw std::runtime_error("Multiplication is not supported for strings");
}

API_MI_ String String::operator/(const String& other) const {
    throw std::runtime_error("Division is not supported for strings");
}

API_MI_ String String::operator+(int other) const {
    return String(value_.getString() + std::to_string(other));
}

API_MI_ String String::operator-(int other) const {
    throw std::runtime_error("Subtraction is not supported for strings");
}

API_MI_ String String::operator*(int other) const {
    throw std::runtime_error("Multiplication is not supported for strings");
}

API_MI_ String String::operator/(int other) const {
    throw std::runtime_error("Division is not supported for strings");
}

API_MI_ String& String::operator+=(const String& other) {
    value_ = value_.getString() + other.value_.getString();
    return *this;
}

API_MI_ String& String::operator-=(const String& other) const
{
    throw std::runtime_error("Subtraction is not supported for strings");
}

API_MI_ String& String::operator*=(const String& other) const
{
    throw std::runtime_error("Multiplication is not supported for strings");
}

API_MI_ String& String::operator/=(const String& other) const
{
    throw std::runtime_error("Division is not supported for strings");
}

API_MI_ String String::operator[](const int index) const {
    return String(std::string(1, value_.getString()[index]));
}

API_MI_ String& String::operator[](const int index) {
    value_ = std::string(1, value_.getString()[index]);
    return *this;
}

API_MI_ String& String::slice(const int* cbegin, const int* cend) {
    value_ = std::string(cbegin, cend);
    return *this;
}

API_MI_ String String::slice(const int begin, const int end) const {
    return String(value_.getString().substr(begin, end - begin));
}

API_MI_ std::string::size_type String::size() const {
    return value_.getString().size();
}

API_MI_ void String::append(const String& string) {
    value_ = value_.getString() + string.value_.getString();
}

API_MI_ String String::substring(const int start, const int end) const {
    return String(value_.getString().substr(start, end - start));
}

API_MI_ String String::trim() const {
    std::string str = value_.getString();
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return String(str);
}

API_MI_ std::string::const_iterator String::begin() const {
    return value_.getString().begin();
}

API_MI_ std::string::const_iterator String::end() const {
    return value_.getString().end();
}

API_MI_ bool String::startsWith(const String& prefix) const {
    return value_.getString().find(prefix.value_.getString()) == 0;
}

API_MI_ bool String::endsWith(const String& suffix) const {
    const std::string& str = value_.getString();
    const std::string& suff = suffix.value_.getString();
    return str.size() >= suff.size() && str.compare(str.size() - suff.size(), suff.size(), suff) == 0;
}

API_MI_ String String::toUpperCase() const {
    std::string str = value_.getString();
    for (auto& c : str) {
        c = std::toupper(c);
    }
    return String(str);
}

API_MI_ String String::toLowerCase() const {
    std::string str = value_.getString();
    for (auto& c : str) {
        c = std::tolower(c);
    }
    return String(str);
}

API_MI_ std::vector<String> String::split(const String& delimiter) const {
    std::vector<String> result;
    std::string str = value_.getString();
    const std::string del = delimiter.value_.getString();
    size_t pos = 0;
    while ((pos = str.find(del)) != std::string::npos) {
        result.emplace_back(str.substr(0, pos));
        str.erase(0, pos + del.length());
    }
    result.emplace_back(str);
    return result;
}

API_MI_ std::vector<String> String::split(const char* str) const{
    std::vector<String> result;
    std::string s = value_.getString();
    const std::string del(str);
    size_t pos = 0;
    while ((pos = s.find(del)) != std::string::npos) {
        result.emplace_back(s.substr(0, pos));
        s.erase(0, pos + del.length());
    }
    result.emplace_back(s);
    return result;
}
API_MI_ std::vector<String> String::split(const std::string& str) const{
    std::vector<String> result;
    std::string s = value_.getString();
    const std::string& del(str);
    size_t pos = 0;
    while ((pos = s.find(del)) != std::string::npos) {
        result.emplace_back(s.substr(0, pos));
        s.erase(0, pos + del.length());
    }
    result.emplace_back(s);
    return result;
}

API_MI_ String String::repeat(const int count) const {
    std::string str = value_.getString();
    for (int i = 0; i < count - 1; ++i) {
        str += value_.getString();
    }
    return String(str);
}

API_MI_ String String::replace(const String& from, const String& to) const {
    std::string str = value_.getString();
    const std::string f = from.value_.getString();
    const std::string t = to.value_.getString();
    size_t start_pos = 0;
    while ((start_pos = str.find(f, start_pos)) != std::string::npos) {
        str.replace(start_pos, f.length(), t);
        start_pos += t.length();
    }
    return String(str);
}

API_MI_ String String::replace(const char* from, const char* to) const
{
    std::string str = value_.getString();
    const std::string f(from);
    const std::string t(to);
    size_t start_pos = 0;
    while ((start_pos = str.find(f, start_pos)) != std::string::npos) {
        str.replace(start_pos, f.length(), t);
        start_pos += t.length();
    }
    return String(str);
}

API_MI_ String String::replace(const std::string& from, const std::string& to) const
{
    std::string str = value_.getString();
    const std::string& f = from;
    const std::string& t = to;
    size_t start_pos = 0;
    while ((start_pos = str.find(f, start_pos)) != std::string::npos) {
        str.replace(start_pos, f.length(), t);
        start_pos += t.length();
    }
    return String(str);
}
API_MI_ int String::indexOf(const String& substring) const {
    return value_.getString().find(substring.value_.getString());
}

API_MI_ int String::indexOf(const char* str) const
{
    return value_.getString().find(str);
}

API_MI_ int String::indexOf(const std::string& str) const
{
    return value_.getString().find(str);
}


API_MI_ bool String::operator==(const std::string& other) const {
    return value_.getString() == other;
}

API_MI_ bool String::operator!=(const std::string& other) const {
    return value_.getString() != other;
}

API_MI_ std::string::const_iterator String::cbegin() const {
    return value_.getString().cbegin();
}

API_MI_ std::string::const_iterator String::cend() const {
    return value_.getString().cend();
}

API_MI_ std::string::const_reverse_iterator String::crbegin() const {
    return value_.getString().crbegin();
}

API_MI_ std::string::const_reverse_iterator String::crend() const {
    return value_.getString().crend();
}

API_MI_ std::string::const_reverse_iterator String::rbegin() const{
    return value_.getString().rbegin();
}

API_MI_ std::string::const_reverse_iterator String::rend() const {
    return value_.getString().rend();
}






API_MI_END
