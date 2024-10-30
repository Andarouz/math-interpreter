#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <map>

#include "history.h"
#include "../core.hpp"
#include "lexer.h"
#include "../typing/matrix.h"
#include "../typing/rational.h"
#include "../typing/variable.h"
#include "../typing/vector.h"

API_MI_BEGIN
class Interpreter final {
public API_METHODS:
    API_MI_ enum class MODE {
        FILE_READ,
        CONSOLE,
        GUI
    };

    API_MI_ enum class VariableType {
        Vector,
        Matrix,
        Number,
        Rational,
        Unknown
    };

    API_MI_ Interpreter();
    API_MI_ ~Interpreter() = default;

    API_MI_ void start(MODE);

protected:
    API_MI_ void run();

    [[nodiscard]]
    API_MI_ bool read();

    [[nodiscard]]
    API_MI_ bool write();
private
    API_METHODS : static VariableType determineVariableType(const std::string& type);
    void addVariableToMap(const std::string& name, VariableType type,
                          const std::string& value);
    void search_variable(const std::string& keyName);

private API_VARIABLES:

    API_MI_ Lexer lexer_;
    API_MI_ History history_;

    // // API_MI_ std::map<std::string, Variable> variables_;
    // API_MI_ std::map<std::string, Vector> vectors_table_;
    // API_MI_ std::map<std::string, Matrix> matrix_table_;
    // API_MI_ std::map<std::string, Number> numbers_table_;
    // API_MI_ std::map<std::string, Rational> rational_table_;
    API_MI_ std::map<std::string, std::string> vectors_table_;
    API_MI_ std::map<std::string, std::string> matrix_table_;
    API_MI_ std::map<std::string, std::string> numbers_table_;
    API_MI_ std::map<std::string, std::string> rational_table_;

};

API_MI_END

#endif //INTERPRETER_H