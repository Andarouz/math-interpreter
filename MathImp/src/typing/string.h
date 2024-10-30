//
// Created by gavri on 27.10.2024.
//

#ifndef STRING_H
#define STRING_H

#include <vector>

#include "variable.h"

API_MI_BEGIN
class String final : public AbstractObject {
public API_METHODS:
    API_MI_ String();
    API_MI_ explicit String(Variable value);
    API_MI_ explicit String(const std::string& value);
    API_MI_ explicit String (const char* value);
    API_MI_ String(const String& other);
    API_MI_ String(String&& other) noexcept;
    API_MI_ ~String() override = default;

    [[nodiscard]]
    API_MI_ std::string hex() const override;

    [[nodiscard]]
    API_MI_ std::string dec() const override;

    [[nodiscard]]
    API_MI_ std::string oct() const override;

    [[nodiscard]]
    API_MI_ std::string bin() const override;

    API_MI_ String& operator=(const String& other);
    API_MI_ String& operator=(String&& other) noexcept;
    API_MI_ String& operator=(Variable value);
    API_MI_ String& operator=(const std::string& value);
    API_MI_ String& operator=(const char* value);

    API_MI_ bool operator==(const String& other) const;
    API_MI_ bool operator!=(const String& other) const;
    API_MI_ String operator+(const String& other) const;
    API_MI_ String operator-(const String& other) const;
    API_MI_ String operator*(const String& other) const;
    API_MI_ String operator/(const String& other) const;


    API_MI_ bool operator==(const std::string& other) const;
    API_MI_ bool operator!=(const std::string& other) const;

    API_MI_ String operator+(int other) const;
    API_MI_ String operator-(int other) const;
    API_MI_ String operator*(int other) const;
    API_MI_ String operator/(int other) const;

    API_MI_ String& operator+=(const String& other);
    API_MI_ String& operator-=(const String& other) const;
    API_MI_ String& operator*=(const String& other) const;
    API_MI_ String& operator/=(const String& other) const;

    API_MI_ String operator[](int index) const;
    API_MI_ String& operator[](int index);

    [[nodiscard]]
    API_MI_ String& slice(const int* cbegin, const int* cend);

    [[nodiscard]]
    API_MI_ String slice(const int begin, const int end) const;
    [[nodiscard]]
    API_MI_ std::string::size_type size() const;

    API_MI_ void append(const String& string);

    // Возвращает подстроку от start до end
    [[nodiscard]]
    API_MI_ String substring(int start, int end) const;

    [[nodiscard]]
    // Удаляет пробелы в начале и конце строки
    API_MI_ String trim() const;

    // Возвращает true, если строка начинается с указанного префикса
    [[nodiscard]]
    API_MI_ bool startsWith(const String& prefix) const;

    // Возвращает true, если строка заканчивается на указанный суффикс
    [[nodiscard]]
    API_MI_ bool endsWith(const String& suffix) const;

    [[nodiscard]]
    // Преобразует все символы строки в верхний регистр
    API_MI_ String toUpperCase() const;

    [[nodiscard]]
    // Преобразует все символы строки в нижний регистр
    API_MI_ String toLowerCase() const;

    // Разделяет строку по указанному разделителю и возвращает вектор подстрок
    [[nodiscard]]
    API_MI_ std::vector<String> split(const String& delimiter) const;

    [[nodiscard]]
    API_MI_ std::vector<String> split(const char* str) const;

    [[nodiscard]]
    API_MI_ std::vector<String> split(const std::string& str) const;
    [[nodiscard]]
    // Возвращает строку, состоящую из указанного числа повторений текущей строки
    API_MI_  String repeat(int count) const;

    [[nodiscard]]
    // Заменяет все вхождения подстроки на другую подстроку
    API_MI_ String replace(const String& from, const String& to) const;

    [[nodiscard]]
    API_MI_ String replace(const char* from, const char* to) const;

    [[nodiscard]]
    API_MI_ String replace(const std::string& from, const std::string& to) const;
    // Возвращает позицию первого вхождения подстроки, или -1, если не найдено
    [[nodiscard]]
    API_MI_ int indexOf(const String& substring) const;

    [[nodiscard]]
    API_MI_ int indexOf(const char* str) const;

    [[nodiscard]]
    API_MI_ int indexOf(const std::string& str) const;
    [[nodiscard]]
    API_MI_ std::string::const_iterator begin() const;

    [[nodiscard]]
    API_MI_ std::string::const_iterator end() const;

    [[nodiscard]]
    API_MI_ std::string::const_reverse_iterator rbegin() const;

    [[nodiscard]]
    API_MI_ std::string::const_reverse_iterator rend() const;

    [[nodiscard]]
    API_MI_ std::string::const_iterator cbegin() const;

    [[nodiscard]]
    API_MI_ std::string::const_iterator cend() const;

    [[nodiscard]]
    API_MI_ std::string::const_reverse_iterator crbegin() const;

    [[nodiscard]]
    API_MI_ std::string::const_reverse_iterator crend() const;


private API_VARIABLES:
    API_MI_ Variable value_;
};
API_MI_END


#endif //STRING_H
