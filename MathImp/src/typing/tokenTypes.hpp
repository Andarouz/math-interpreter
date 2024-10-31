//
// Created by massonskyi on 28.10.24.
//

#ifndef TOKENTYPES_HPP
#define TOKENTYPES_HPP
#include "../core.hpp"
#include <string>
#include <cctype>
#include <set>
#include <sstream>
API_MI_BEGIN

API_MI_ enum class TokenType {
    TYPE_VARIABLE,
    NAME_VARIABLE,
    OPERATOR,
    VALUE,
    END_LINE,
    VECTOR,
    MATRIX,
    RATIONAL,
    UNKNOWN
};

// Базовый интерфейс для всех типов токенов
API_MI_ struct BaseToken {
    API_MI_ virtual ~BaseToken() = default;
    [[nodiscard]]
    API_MI_ virtual bool match(const std::string& input) const = 0;
    [[nodiscard]]
    API_MI_ virtual TokenType getType() const = 0;
};

API_MI_ struct TypeVariableToken final : BaseToken {
    API_MI_ TypeVariableToken() {
            std::istringstream iss(RESERVED_WORDS);
            std::string word;
            while (iss >> word) {
                reservedWords_.insert(word);
            }
        }

    [[nodiscard]]
    API_MI_ bool match(const std::string& input) const override {
        return reservedWords_.contains(input);
    }

    [[nodiscard]]
    API_MI_ TokenType getType() const override {
        return TokenType::TYPE_VARIABLE;
    }

private:
    API_MI_ std::set<std::string> reservedWords_;
};

// Токены для имен переменных
API_MI_ struct NameVariableToken final : BaseToken {
    [[nodiscard]]
    API_MI_ bool match(const std::string& input) const override {
        return std::isalpha(input[0]) || input[0] == '_';
    }
    [[nodiscard]]
    API_MI_ TokenType getType() const override {
        return TokenType::NAME_VARIABLE;
    }
};

// Новый `OperatorToken` для поддержания математических операций
API_MI_ struct OperatorToken final : BaseToken {
    API_MI_ OperatorToken() {
        std::istringstream iss(RESERVED_OPERATORS);
        std::string word;
        while (iss >> word) {
            reservedOperators_.insert(word);
        }
    }
    [[nodiscard]]
    API_MI_ bool match(const std::string& input) const override {
        return reservedOperators_.contains(input);
    }
    [[nodiscard]]
    API_MI_ TokenType getType() const override {
        return TokenType::OPERATOR;
    }
private:
    std::set<std::string> reservedOperators_;
};

// Токены для числовых значений
API_MI_ struct ValueToken final : BaseToken {
    [[nodiscard]]
    API_MI_ bool match(const std::string& input) const override {
        return std::isdigit(input[0]) || (input[0] == '.' && input.size() > 1);
    }
    [[nodiscard]] API_MI_ TokenType getType() const override {
        return TokenType::VALUE;
    }
};
API_MI_ struct VecToken final : BaseToken {
    [[nodiscard]]
    API_MI_ bool match(const std::string& token) const override {
        return token.front() == '[' && token.back() == ']' && token.find(',') != std::string::npos;
    }

    [[nodiscard]]
    API_MI_ TokenType getType() const override {
        return TokenType::VECTOR;
    }
};

API_MI_ struct MatToken final : BaseToken {
    [[nodiscard]]
    API_MI_ bool match(const std::string& token) const override {
        if (token.front() != '[' || token.back() != ']') {
            return false;
        }
        int bracketCount = 0;
        for (char ch : token) {
            if (ch == '[') {
                bracketCount++;
            } else if (ch == ']') {
                bracketCount--;
            }
            if (bracketCount < 0) {
                return false;
            }
        }
        return bracketCount == 0 && token.find("],[") != std::string::npos;
    }

    [[nodiscard]]
    API_MI_ TokenType getType() const override {
        return TokenType::MATRIX;
    }
};
class BracketToken final : public BaseToken {
public:
    bool match(const std::string& token) const override {
        return token == "[" || token == "]";
    }

    TokenType getType() const override {
        return TokenType::VECTOR; // Можно изменить тип, если нужно
    }
};
API_MI_END
#endif //TOKENTYPES_HPP
