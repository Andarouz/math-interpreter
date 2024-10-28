//
// Created by massonskyi on 28.10.24.
//
#include "lexer.h"
API_MI_NAMESPACE Lexer::Lexer() : errorHandler_() {
    // Добавляем типы токенов в список
    tokenMatchers_.emplace_back(std::make_unique<TypeVariableToken>());
    tokenMatchers_.emplace_back(std::make_unique<NameVariableToken>());
    tokenMatchers_.emplace_back(std::make_unique<OperatorToken>());
    tokenMatchers_.emplace_back(std::make_unique<ValueToken>());
}

API_MI_BEGIN

std::vector<Lexer::Token> Lexer::tokenize(const std::string& input) const {
    std::vector<Token> tokens;

    std::string::size_type pos = 0;
    while (pos < input.size()) {
        std::string currToken;
        while (pos < input.size() && !std::isspace(input[pos])) {
            currToken += input[pos++];
        }
        ++pos; // Пропуск пробела

        bool matched = false;
        for (const auto& matcher : tokenMatchers_) {
            if (matcher->match(currToken)) {
                tokens.push_back({matcher->getType(), currToken});
                matched = true;
                break;
            }
        }

        if (!matched && !currToken.empty()) {
            tokens.push_back({TokenType::UNKNOWN, currToken});
        }
    }

    validate(tokens);

    return tokens;
}

const ErrorHandler& Lexer::getErrorHandler() const {
    return errorHandler_;
}

void Lexer::validate(const std::vector<Lexer::Token>& tokens) const {
    checkUnmatchedBrackets(tokens);
    checkInvalidTokens(tokens);
    checkMissingSemicolons(tokens);
    checkInvalidVariableDeclarations(tokens);
}

void Lexer::checkUnmatchedBrackets(const std::vector<Lexer::Token>& tokens) const {
    int openBrackets = 0;
    for (const auto& [type, value] : tokens) {
        if (type == TokenType::VECTOR || type == TokenType::MATRIX) {
            openBrackets++;
        }
        if (type == TokenType::UNKNOWN && value == "]") {
            if (openBrackets == 0) {
                errorHandler_.show_error_position("Unmatched closing bracket");
            } else {
                openBrackets--;
            }
        }
    }
    if (openBrackets > 0) {
        errorHandler_.show_error_position("Unmatched opening bracket");
    }
}

void Lexer::checkInvalidTokens(const std::vector<Lexer::Token>& tokens) const {
    for (const auto& [type, value] : tokens) {
        if (type == TokenType::UNKNOWN) {
            errorHandler_.show_error_position("Invalid token");
        }
    }
}

void Lexer::checkMissingSemicolons(const std::vector<Lexer::Token>& tokens) const {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (i + 1 < tokens.size() && (tokens[i].type == TokenType::VALUE || tokens[i].type == TokenType::NAME_VARIABLE)) {
            if (tokens[i + 1].type != TokenType::OPERATOR || tokens[i + 1].value != ";") {
                errorHandler_.show_error_position("Missing semicolon");
            }
        }
    }
}

void Lexer::checkInvalidVariableDeclarations(const std::vector<Lexer::Token>& tokens) const {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (const auto& [type, value] = tokens[i]; type == TokenType::TYPE_VARIABLE || type == TokenType::NAME_VARIABLE) {
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::UNKNOWN) {
                errorHandler_.show_error_position("Invalid variable declaration");
            }
        }
    }
}
API_MI_END