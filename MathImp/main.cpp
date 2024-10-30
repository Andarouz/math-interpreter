#include "src/base/interpreter.h"
#include "src/core.hpp"

int main() {
    API_MI_NAMESPACE Interpreter interpreter;
    interpreter.start(API_MI_NAMESPACE Interpreter::MODE::CONSOLE);
    return 0;
}