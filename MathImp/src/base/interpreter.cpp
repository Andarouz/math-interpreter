#include "interpreter.h"
#include <cstdlib>
#include <thread>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <variant>

API_MI_BEGIN

API_MI_ inline std::string trim(const std::string &str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }

    auto end = str.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// Helper function to print a variant type
void printVariant(const std::variant<int, float, Vector, Matrix>& var) {
    std::visit([](const auto& arg) {
        std::cout << arg << std::endl;
    }, var);
}

// Function to evaluate operations between two tokens (operands)
template <typename T>
T applyOperator(const std::variant<int, float, Vector, Matrix>& lhs, const std::variant<int, float, Vector, Matrix>& rhs, const std::string& op) {
    return std::visit(
            [&op]<typename T0, typename T1>(T0&& lhsVal, T1&& rhsVal) -> T {
        using LHS = std::decay_t<T0>;
        using RHS = std::decay_t<T1>;

        if constexpr (std::is_same_v<LHS, int> && std::is_same_v<RHS, int>) {
            if (op == "+") return lhsVal + rhsVal;
            if (op == "-") return lhsVal - rhsVal;
            if (op == "*") return lhsVal * rhsVal;
            if (op == "/") {
                if (rhsVal == 0) throw std::runtime_error("Division by zero");
                return lhsVal / rhsVal;
            }
        } else if constexpr (std::is_same_v<LHS, Vector> && std::is_same_v<RHS, Vector>) {
            return applyOperator(lhsVal, rhsVal, op); // Use the vector-specific overload
        } else if constexpr (std::is_same_v<LHS, Matrix> && std::is_same_v<RHS, Matrix>) {
            // Implement matrix operations if necessary
            throw std::runtime_error("Matrix operations are not yet implemented.");
        }
        throw std::runtime_error("Unsupported operator or operand types");
    }, lhs, rhs);
}

// // Overload for vector operations (e.g., scalar multiplication)
Vector applyOperator(const Vector& lhs, const Vector& rhs, const std::string& op) {
    // Ensure both vectors are the same size
    if (lhs.size() != rhs.size()) throw std::runtime_error("Vector size mismatch");

    Vector result;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (op == "+") result.append(lhs[i] + rhs[i]);
        else if (op == "-") result.append(lhs[i] - rhs[i]);
        else if (op == "*") result.append(lhs[i] * rhs[i]);
        if (op == "/") {
            if (rhs[i].isZero()) throw std::runtime_error("Division by zero");
            result.append(lhs[i] / rhs[i]);
        }
        else throw std::runtime_error("Unsupported operator for vectors: " + op);
    }
    return result;
}

API_MI_ Interpreter::Interpreter() : lexer_(), history_(999), variables_() {
}

API_MI_ void Interpreter::start(const MODE mode) {
    switch (mode) {
        case MODE::CONSOLE:
            run();
            break;
        case MODE::FILE_READ:
            // TODO: Add your file read logic here
            break;
        case MODE::GUI:
            // TODO: Add your GUI logic here
            break;
        default:
            throw std::invalid_argument("Invalid mode specified.");
    }
}

void Interpreter::run() {
    std::cout << "Welcome to the MI Interpreter!" << std::endl;

    std::thread inputThread([this]() {
        std::string input_;
        while (true) {
            std::cout << ">>> ";
            std::getline(std::cin, input_);

            if (input_ == "exit") {
                break;
            }

            if (input_ == "history") {
                history_.show();
                continue;
            }

            if (input_.find("print(") == 0 && input_.back() == ')') {
                std::string keyName = input_.substr(6, input_.size() - 7); // Extract the keyName
                searchVariable(keyName);
                continue;
            }

            // Tokenize the input
            auto tokens = lexer_.tokenize(input_);
            if (tokens.empty()) continue;
            if (tokens.back().value == ";") {
                tokens.pop_back();
            }

            // Process assignment or expression
            if (isAssignment(tokens)) {
                processAssignment(tokens);
            } else {
                if (checkVariableInMap(tokens[1].value)) {
                    // This ensures the variable is stored correctly
                    addVariableToMap(tokens[1].value, tokens[1].value);
                }
                printVariant(evaluateExpression(tokens));
            }
            history_.add(input_);
        }
    });

    inputThread.join();
}

// Helper function to check if input is an assignment
bool Interpreter::isAssignment(const std::vector<Lexer::Token>& tokens) {
    return tokens.size() > 1 && tokens[1].value == "=";
}

void Interpreter::processAssignment(const std::vector<Lexer::Token>& tokens) {
    const std::string varName = tokens[0].value;

    // Evaluate the expression and store result based on its type
    const auto result = evaluateExpression({tokens.begin() + 2, tokens.end()});
    variables_[varName] = result; // Directly store result

}

void Interpreter::searchVariable(const std::string& keyName) {
    if (const auto it = variables_.find(keyName); it != variables_.end()) {
        printVariant(it->second);
    } else {
        std::cout << keyName << " undefined." << std::endl;
    }
}

Interpreter::VariableType Interpreter::determineVariableType(const std::string& type) {
    if (type == "vec") return VariableType::Vector;
    if (type == "mat") return VariableType::Matrix;
    if (type == "int" || type == "float") return VariableType::Number;
    if (type == "rat") return VariableType::Rational;
    return VariableType::Unknown;
}
bool Interpreter::checkVariableInMap(const std::string& name) const {
    return variables_.contains(name);
}

void Interpreter::addVariableToMap(const std::string& name, const std::string& value) {
    try {
        // Add the variable to the appropriate table
        variables_[name] = stringToVariant(value); // Store the value directly
    } catch (const std::bad_variant_access&) {
        std::cerr << "Error: Incorrect type in variant for variable '" << name << "'" << std::endl;
    }
}

Vector Interpreter::parseStringToVector(const std::string& input) {
    Vector result;
    std::string trimmedInput = trim(input);

    // Remove the brackets
    if (trimmedInput.front() == '[' && trimmedInput.back() == ']') {
        trimmedInput = trimmedInput.substr(1, trimmedInput.size() - 2);
    }

    std::istringstream stream(trimmedInput);
    std::string token;

    while (std::getline(stream, token, ',')) {
        token = trim(token);
        std::istringstream tokenStream(token);
        if (int num; tokenStream >> num) { // Check for valid integer conversion
            result.append(Number(num)); // Assuming Number is a valid type
        }
    }

    return result;
}

Matrix Interpreter::parseStringToMatrix(const std::string& input) {
    Matrix result;
    std::string trimmedInput = trim(input);

    // Remove the outer brackets
    if (trimmedInput.front() == '[' && trimmedInput.back() == ']') {
        trimmedInput = trimmedInput.substr(1, trimmedInput.size() - 2);
    }

    std::istringstream stream(trimmedInput);
    std::string token;

    while (std::getline(stream, token, ']')) {
        if (const size_t openBracketPos = token.find('['); openBracketPos != std::string::npos) {
            std::string vectorString = token.substr(openBracketPos + 1);
            vectorString = trim(vectorString);
            if (!vectorString.empty()) {
                result.append(parseStringToVector("[" + vectorString + "]"));
            }
        }

        // Skip the comma after the closing bracket
        if (stream.peek() == ',') {
            stream.ignore();
        }
    }

    return result;
}
std::variant<int, float, Vector, Matrix> Interpreter::stringToVariant(const std::string& input) {
    // Trim the input string
    const std::string trimmedInput = trim(input);

    // Check if the input is an integer
    try {
        size_t pos;
        int intValue = std::stoi(trimmedInput, &pos);
        if (pos == trimmedInput.size()) {
            return intValue;
        }
    } catch (const std::invalid_argument&) {
        // Not an integer
    }

    // Check if the input is a float
    try {
        size_t pos;
        float floatValue = std::stof(trimmedInput, &pos);
        if (pos == trimmedInput.size()) {
            return floatValue;
        }
    } catch (const std::invalid_argument&) {
        // Not a float
    }

    // Check if the input is a Vector
    if (trimmedInput.front() == '[' && trimmedInput.back() == ']') {
        return parseStringToVector(trimmedInput);
    }

    // Check if the input is a Matrix
    if (trimmedInput.front() == '[' && trimmedInput.back() == ']') {
        return parseStringToMatrix(trimmedInput);
    }

    // If none of the above, throw an error
    throw std::runtime_error("Invalid input string: " + input);
}
// New function to evaluate expressions
std::variant<int, float, Vector, Matrix> Interpreter::evaluateExpression(const std::vector<Lexer::Token>& tokens) {
    std::vector<std::variant<int, float, Vector, Matrix>> values;
    std::vector<std::string> operators;

    // Parse tokens
    for (const auto &[type, value] : tokens) {
        if (type == TokenType::VALUE) {
            // Check if the value is a variable name
            if (variables_.contains(value)) {
                values.emplace_back(std::visit([](const auto& arg) -> std::variant<int, float, Vector, Matrix> {
                    return arg; // Return the value directly
                }, variables_[value]));
            } else {
                // Try to convert to integer
                try {
                    values.emplace_back(std::stoi(value)); // Assume it's an integer if not a variable
                } catch (const std::invalid_argument&) {
                    throw std::runtime_error("Invalid token value: " + value);
                }
            }
        } else if (type == TokenType::OPERATOR) {
            operators.push_back(value);
        } else if (type == TokenType::VECTOR) {
            values.emplace_back(parseStringToVector(value));
        } else if (type == TokenType::MATRIX) {
            values.emplace_back(parseStringToMatrix(value));
        }
    }

    // If there is only one value and no operators, return the value directly
    if (values.size() == 1 && operators.empty()) {
        return values[0];
    }

    // Apply operators left to right (basic implementation, could be improved with precedence)
    while (!operators.empty() && values.size() > 1) {
        auto lhs = values[0];
        auto rhs = values[1];
        auto op = operators[0];

        // Perform operation
        auto result = applyOperator<std::variant<int, float, Vector, Matrix>>(lhs, rhs, op);

        // Replace the first two values with the result
        values.erase(values.begin(), values.begin() + 2);
        values.insert(values.begin(), result);
        operators.erase(operators.begin());
    }

    // If there's one value left, return it
    if (values.size() == 1) {
        return values[0]; // Return the final value
    }

    throw std::runtime_error("Invalid expression evaluation: More than one value remains without operators.");
}
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0; // For unknown operators
}

API_MI_END
