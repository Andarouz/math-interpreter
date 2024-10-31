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
        enum class MODE {
        FILE_READ,
        CONSOLE,
        GUI
    };

    enum class VariableType {
        Vector,
        Matrix,
        Number,
        Rational,
        Unknown
    };

    Interpreter();
    ~Interpreter() = default;

    void start(MODE mode);

protected:
    void run();
    [[nodiscard]] bool read();
    [[nodiscard]] bool write();

private API_METHODS:
    static VariableType determineVariableType(const std::string& type);
    void addVariableToMap(const std::string& name, const std::string& value);
    void searchVariable(const std::string& keyName);
    static Matrix parseStringToMatrix(const std::string& input);
    static Vector parseStringToVector(const std::string &input);
    static std::variant<int, float, Vector, Matrix> stringToVariant(const std::string& input);
    bool checkVariableInMap(const std::string& name) const;
    std::variant<int, float, Vector, Matrix> evaluateExpression(const std::vector<Lexer::Token>& tokens);
    [[nodiscard]] static bool isAssignment(const std::vector<Lexer::Token>& tokens);
    void processAssignment(const std::vector<Lexer::Token>& tokens);

private API_VARIABLES:
    Lexer lexer_;
    History history_;
    std::map<std::string, std::variant<int, float, Vector, Matrix>> variables_;
};

API_MI_END

#endif //INTERPRETER_H