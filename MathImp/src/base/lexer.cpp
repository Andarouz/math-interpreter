//
// Created by massonskyi on 28.10.24.
//
#include "lexer.h"
API_MI_NAMESPACE Lexer::Lexer() : errorHandler_(true) {
    // Добавляем типы токенов в список
    tokenMatchers_.emplace_back(std::make_unique<TypeVariableToken>());
    tokenMatchers_.emplace_back(std::make_unique<NameVariableToken>());
    tokenMatchers_.emplace_back(std::make_unique<OperatorToken>());
    tokenMatchers_.emplace_back(std::make_unique<ValueToken>());
    tokenMatchers_.emplace_back(std::make_unique<VecToken>());
    tokenMatchers_.emplace_back(std::make_unique<MatToken>());
}

API_MI_BEGIN

std::vector<Lexer::Token> Lexer::tokenize(const std::string& input) const {
    std::vector<Token> tokens;
    std::string::size_type pos = 0;

    checkUnmatchedBrackets(input);

    while (pos < input.size()) {
        std::string currToken;
        while (pos < input.size() && !std::isspace(input[pos]) && input[pos] != ';') {
            currToken += input[pos++];
        }

        if (!currToken.empty()) {
            bool matched = false;
            for (const auto& matcher : tokenMatchers_) {
                if (matcher->match(currToken)) {
                    tokens.push_back({matcher->getType(), currToken});
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                tokens.push_back({TokenType::UNKNOWN, currToken});
            }
        }

        if (pos < input.size() && input[pos] == ';') {
            tokens.push_back({TokenType::OPERATOR, ";"});
            ++pos;
        }

        while (pos < input.size() && std::isspace(input[pos])) {
            ++pos; // Skip whitespace
        }
    }

    validate(tokens);
    return tokens;
}
const ErrorHandler& Lexer::getErrorHandler() const {
    return errorHandler_;
}

void Lexer::validate(const std::vector<Lexer::Token>& tokens) const {
    checkInvalidTokens(tokens);
    checkMissingSemicolons(tokens);
    checkInvalidVariableDeclarations(tokens);
}

void Lexer::checkUnmatchedBrackets(const std::string& input) const {
    int openBrackets = 0;
    for (std::size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '[') {
            openBrackets++;
        } else if (input[i] == ']') {
            if (openBrackets == 0) {
                errorHandler_.show_error_position("Unmatched closing bracket", i, "Unmatched closing bracket", ErrorHandler::ErrorType::UnmatchedBracket);
            } else {
                openBrackets--;
            }
        }
    }
    if (openBrackets > 0) {
        errorHandler_.show_error_position("Unmatched opening bracket", input.size(), "Unmatched opening bracket", ErrorHandler::ErrorType::UnmatchedBracket);
    }
}

void Lexer::checkInvalidTokens(const std::vector<Lexer::Token>& tokens) const {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (const auto &[type, value] = tokens[i];type == TokenType::UNKNOWN) {
            errorHandler_.show_error_position(value, i, "Invalid token", ErrorHandler::ErrorType::InvalidType);
        }
    }
}

void Lexer::checkMissingSemicolons(const std::vector<Lexer::Token>& tokens) const {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == TokenType::VALUE || tokens[i].type == TokenType::NAME_VARIABLE) {
            // Check for semicolon after value or name variable
            if (i + 1 < tokens.size() && tokens[i + 1].type != TokenType::OPERATOR && tokens[i + 1].value != ";") {
                errorHandler_.show_error_position(tokens[i].value, i, "Missing semicolon", ErrorHandler::ErrorType::SyntaxError);
            }
        } else if (tokens[i].type == TokenType::VECTOR || tokens[i].type == TokenType::MATRIX) {
            // Check for semicolon after vector or matrix declaration
            std::size_t j = i + 1;
            int bracketCount = 1;
            while (j < tokens.size() && bracketCount > 0) {
                if (tokens[j].value == "[") {
                    bracketCount++;
                } else if (tokens[j].value == "]") {
                    bracketCount--;
                }
                j++;
            }
            if (j < tokens.size() && tokens[j].value != ";") {
                errorHandler_.show_error_position(tokens[j - 1].value, j - 1, "Missing semicolon after vector/matrix declaration", ErrorHandler::ErrorType::SyntaxError);
            }
        }
    }
}

void Lexer::checkInvalidVariableDeclarations(const std::vector<Lexer::Token>& tokens) const {
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        if (const auto &[type, value] = tokens[i]; type == TokenType::TYPE_VARIABLE || type == TokenType::NAME_VARIABLE) {
            if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::UNKNOWN) {
                errorHandler_.show_error_position(value, i, "Invalid variable declaration", ErrorHandler::ErrorType::InvalidType);
            }
        }
    }
}
API_MI_END