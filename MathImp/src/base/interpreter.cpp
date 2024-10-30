#include "interpreter.h"
#include <cstdlib>
API_MI_BEGIN

API_MI_ Interpreter::Interpreter() : lexer_(), history_(999), vectors_table_() {
}
API_MI_ void Interpreter::start(const MODE mode) {
    switch (mode) {
        case MODE::CONSOLE:
            run();
        break;
        case MODE::FILE_READ:
            // Add your file read logic here
            break;
        case MODE::GUI:
            // Add your GUI logic here
            break;
        default:
            // Handle unexpected mode
            break;
    }
}

// Main loop for console input handling
API_MI_ void Interpreter::run() {
    std::cout << "Welcome to the MI Interpreter!" << std::endl;

    // Get system information
    std::system("uname -a");

    // Get terminal information
    if (const char *term = std::getenv("TERM")) {
        std::cout << "Terminal: " << term << std::endl;
    } else {
        std::cout << "Terminal information not available." << std::endl;
    }
    std::string input_;
    while (input_ != "exit") {
        std::cout << ">>> ";
        std::getline(std::cin, input_);

        if(input_ == "history") {
            history_.show();
            continue;
        }

        const auto tokens = lexer_.tokenize(input_);

        if (tokens.empty()) {
            continue;
        }
        if(tokens.size() >3 )
            if (const auto type = determineVariableType(tokens[0].value); type != VariableType::Unknown) {
                addVariableToMap(tokens[1].value, type, tokens[3].value);
            }
        if(tokens.size() == 1) {
            search_variable(tokens[0].value);
        }
        history_.add(input_);
    }
}
void Interpreter::search_variable(const std::string& keyName) {
    if (const auto it = vectors_table_.find(keyName); it != vectors_table_.end()) {
        std::cout << "Vector " << keyName << ": " << it->second << std::endl;
    } else if (const auto it = matrix_table_.find(keyName); it != matrix_table_.end()) {
        std::cout << "Matrix " << keyName << ": " << it->second << std::endl;
    } else if (const auto it = numbers_table_.find(keyName); it != numbers_table_.end()) {
        std::cout << "Number " << keyName << ": " << it->second << std::endl;
    } else if (const auto it = rational_table_.find(keyName); it != rational_table_.end()) {
        std::cout << "Rational " << keyName << ": " << it->second << std::endl;
    } else {
        std::cout << "Variable " << keyName << " not found." << std::endl;
    }
}
Interpreter::VariableType Interpreter::determineVariableType(const std::string& type) {
    if (type == "vec") {
        return VariableType::Vector;
    } else if (type == "mat") {
        return VariableType::Matrix;
    } else if (type == "int" || type == "float") {
        return VariableType::Number;
    } else if (type == "rat") {
        return VariableType::Rational;
    } else {
        return VariableType::Unknown;
    }
}
void Interpreter::addVariableToMap(const std::string& name, VariableType type, const std::string& value) {
    try {
        // Check if the key exists in any of the tables
        auto checkAndPrint = [&](const std::map<std::string, std::string>& table, const std::string& tableName) {
            if (const auto it = table.find(name); it != table.end()) {
                std::cout << "Value in " << tableName << " will change from " << it->second << " to " << value << std::endl;
            }
        };

        checkAndPrint(vectors_table_, "vectors_table_");
        checkAndPrint(matrix_table_, "matrix_table_");
        checkAndPrint(numbers_table_, "numbers_table_");
        checkAndPrint(rational_table_, "rational_table_");

        // Add the variable to the appropriate table
        switch (type) {
            case VariableType::Vector:
                vectors_table_[name] = value;
            break;
            case VariableType::Matrix:
                matrix_table_[name] = value;
            break;
            case VariableType::Number:
                numbers_table_[name] = value;
            break;
            case VariableType::Rational:
                rational_table_[name] = value;
            break;
            default:
                std::cerr << "Unknown variable type: " << static_cast<int>(type) << std::endl;
            break;
        }
    } catch (const std::bad_variant_access&) {
        std::cerr << "Error: Incorrect type in variant for variable '" << name << "'" << std::endl;
    }
}
// Detect and process key combinations
API_MI_END