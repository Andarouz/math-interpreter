#include "interpreter.h"

API_MI_BEGIN

Interpreter::Interpreter() : lexer_(), errorHandler_() {}

Variable Interpreter::evaluate(const std::string& expression) {
    const auto tokens = lexer_.tokenize(expression);
    return parseExpression(tokens);
}

Variable Interpreter::parseExpression(const std::vector<Lexer::Token>& tokens) {
    size_t pos = 0;
    Variable result = parseTerm(tokens, pos);

    while (pos < tokens.size() && (tokens[pos].value == "+" || tokens[pos].value == "-")) {
        std::string op = tokens[pos++].value;
        const Variable term = parseTerm(tokens, pos);
        if (op == "+") {
            result += term;
        } else if (op == "-") {
            result -= term;
        }
    }

    return result;
}

Variable Interpreter::parseTerm(const std::vector<Lexer::Token>& tokens, size_t& pos) {
    Variable result = parseFactor(tokens, pos);

    while (pos < tokens.size() && (tokens[pos].value == "*" || tokens[pos].value == "/")) {
        std::string op = tokens[pos++].value;
        Variable factor = parseFactor(tokens, pos);
        if (op == "*") {
            result *= factor;
        } else if (op == "/") {
            result /= factor;
        }
    }

    return result;
}

Variable Interpreter::parseFactor(const std::vector<Lexer::Token>& tokens, size_t& pos) {
    if (tokens[pos].type == TokenType::VALUE) {
        return Variable(std::stoi(tokens[pos++].value));
    } else if (tokens[pos].type == TokenType::NAME_VARIABLE) {
        if (const std::string varName = tokens[pos++].value; variables_.contains(varName)) {
            return variables_[varName];
        } else {
            errorHandler_.show_error_position("Unknown variable: " + varName);
            return {};
        }
    } else if (tokens[pos].value == "(") {
        pos++;
        Variable result = parseExpression(tokens);
        if (tokens[pos].value == ")") {
            pos++;
        } else {
            errorHandler_.show_error_position("Unmatched parenthesis");
        }
        return result;
    } else {
        errorHandler_.show_error_position("Invalid factor");
        return {};
    }
}

API_MI_END