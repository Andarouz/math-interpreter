// Lexer.hpp

#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include <string>
#include <variant>
#include <vector>

#include "../core.hpp"
#include "../typing/matrix.h"
#include "../typing/rational.h"
#include "../typing/tokenTypes.hpp"
#include "../typing/vector.h"
#include "errorHandler.hpp"

API_MI_BEGIN class Variable;
class Lexer final {
    public API_METHODS:
    struct Token {
        TokenType type;
        std::string value;
    };

    API_MI_ Lexer();
    API_MI_ ~Lexer() = default;

    // Основной метод токенизации
    [[nodiscard]]
    API_MI_ std::vector<Token> tokenize(const std::string& input) const;

    // Метод для получения ошибок
    [[nodiscard]]
    API_MI_ const ErrorHandler& getErrorHandler() const ;


    API_MI_ void validate(const std::vector<Token>& tokens) const;
    API_MI_ void checkUnmatchedBrackets(const std::string& input) const;
    API_MI_ void checkInvalidTokens(const std::vector<Token>& tokens) const;
    API_MI_ void checkMissingSemicolons(const std::vector<Token>& tokens) const;
    API_MI_ void checkInvalidVariableDeclarations(const std::vector<Token>& tokens) const;
private API_VARIABLES:
    std::vector<std::unique_ptr<BaseToken>> tokenMatchers_; // Список токенов для проверки
    ErrorHandler errorHandler_; // Обработчик ошибок
};

API_MI_END
#endif // LEXER_HPP