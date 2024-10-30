#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP
#include <cstdio>
#include <iostream>
#include <string>
#include "../core.hpp"
#include "../typing/tokenTypes.hpp"
#include "outputHandler.hpp"

API_MI_BEGIN

class ErrorHandler final {
public:
    enum class ErrorType {
        SyntaxError,
        UnknownVariable,
        InvalidOperation,
        DivisionByZero,
        UnmatchedBracket,
        InvalidType,
        UnknownError
    };
    explicit ErrorHandler(const bool enable_color) : out(enable_color) {}
    static std::string get_recommendation(const ErrorType &type);
    void show_error_position(const std::string &input, size_t position, const std::string &message, ErrorType type) const;

private:
    static bool check_syntax_error(const std::string &input);
    static bool input_checked_types(const std::string &input);
    void indicate_error_position(const std::string &input, size_t position) const;
    void print_error_pointer(const std::string &input, size_t position) const;

    OutputHandler out;
};


inline std::string ErrorHandler::get_recommendation(const ErrorType& type) {
    switch (type) {
        case ErrorType::SyntaxError:
            return "Проверьте расстановку скобок и операторов. Пример: \"int a = 5 + [2 * 3];\".";
        case ErrorType::UnknownVariable:
            return "Убедитесь, что переменная определена перед её использованием. Пример: \"int x; x = 5;\".";
        case ErrorType::InvalidOperation:
            return "Проверьте, поддерживается ли операция для указанных типов данных. Пример: \"int a = 5 / 0;\".";
        case ErrorType::DivisionByZero:
            return "Нельзя делить на ноль. Исправьте знаменатель. Пример: \"double x = 1.0 / (a != 0 ? a : 1);\".";
        case ErrorType::UnmatchedBracket:
            return "Проверьте корректность закрытия скобок. Пример: \"int f = [5 + 3] * 2;\".";
        case ErrorType::InvalidType:
            return "Недопустимый тип. Проверьте синтаксис и логику. Пример: \"int x = 5;\".";
        default:
            return "Неизвестная ошибка. Проверьте синтаксис и логику программы.";
    }
}
inline void ErrorHandler::show_error_position(const std::string& input, const size_t position, const std::string& message, const ErrorType type) const {
    out.err(message + "\n");
    indicate_error_position(input, position);

    const std::string recommendation = get_recommendation(type);
    if (!recommendation.empty()) {
        char error_string[1024] = {0}, input_string[1024] = {0}, recommendation_string[1024] = {0};

        std::snprintf(error_string, sizeof(error_string), "Error: %s\n", message.c_str());
        std::snprintf(input_string, sizeof(input_string), "Input: %s\n", input.c_str());
        std::snprintf(recommendation_string, sizeof(recommendation_string), "Recommendation: %s\n", recommendation.c_str());

        out.err(error_string);
        out.info(input_string);
        out.warn(recommendation_string);
    }
}

inline bool ErrorHandler::check_syntax_error(const std::string& input) {
    int open_bracket = 0;
    for (const char ch : input) {
        if (ch == '[') {
            open_bracket++;
        } else if (ch == ']') {
            open_bracket--;
        }
    }
    return open_bracket != 0;
}

inline void ErrorHandler::indicate_error_position(const std::string& input, const size_t position) const {
    char error_string[1024];
    std::snprintf(error_string, sizeof(error_string), "Error position: %zu\n", position + 1);
    out.err(error_string);
    print_error_pointer(input, position);
}

inline void ErrorHandler::print_error_pointer(const std::string& input, const size_t position) const {
    std::string error_pointer(position, ' ');
    error_pointer += "\n^\n";
    out.err(input);
    out.err(error_pointer);
}

inline bool ErrorHandler::input_checked_types(const std::string& input) {
    std::istringstream stream(input);
    std::string word;

    while (stream >> word) {
        if (TypeVariableToken typeToken; typeToken.match(word)) {
            return true;
        }
    }

    return false;
}

API_MI_END
#endif //ERROR_HANDLER_HPP