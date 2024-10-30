cmake_minimum_required(VERSION 3.28.3)
project(MathImp)

# Устанавливаем стандарт C++23
set(CMAKE_CXX_STANDARD 23)

# Add fmt library
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.0.1
)
FetchContent_MakeAvailable(fmt)
add_library(mathlib STATIC
        src/typing/number.cpp
        src/typing/number.h
        src/core.hpp
        src/typing/abstractObject.hpp
        src/typing/vector.cpp
        src/typing/vector.h
        tests/vector_test.cpp
        src/typing/variable.cpp
        src/typing/variable.h
        src/typing/matrix.cpp
        src/typing/matrix.h
        tests/matrix_test.cpp
        src/typing/rational.cpp
        src/typing/rational.h
        tests/rational_test.cpp
        src/base/interpreter.h
        src/base/lexer.h
        src/base/lexer.cpp
        src/base/errorHandler.hpp
        src/base/history.h
        src/base/history.cpp
        src/typing/string.cpp
        src/typing/string.h
        tests/string_test.cpp
        tests/lexer_test.cpp
        tests/history_test.cpp
        src/typing/tokenTypes.hpp
        src/base/interpreter.cpp
        src/base/outputHandler.hpp
)

# Add the executable target
add_executable(MathImp main.cpp)

# Link the library to the executable
target_link_libraries(MathImp PRIVATE mathlib fmt::fmt)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Ensure the include directories are set
include_directories(${gtest_SOURCE_DIR}/include ${gtest_BINARY_DIR})

enable_testing()

# Add the test executable for Vector tests
add_executable(VectorTests tests/vector_test.cpp
        src/typing/number.cpp
        src/typing/number.h
        src/typing/vector.cpp
        src/typing/vector.h)

# Link Google Test and the library to the Vector test executable
target_link_libraries(VectorTests PRIVATE gtest gtest_main mathlib)

# Add a test for Vector
add_test(NAME VectorTests COMMAND VectorTests)

# Add the test executable for Matrix tests
add_executable(MatrixTests tests/matrix_test.cpp
        src/typing/number.cpp
        src/typing/number.h
        src/typing/vector.cpp
        src/typing/vector.h
        src/typing/matrix.cpp
        src/typing/matrix.h)

# Link Google Test and the library to the Matrix test executable
target_link_libraries(MatrixTests PRIVATE gtest gtest_main mathlib)

# Add a test for Matrix
add_test(NAME MatrixTests COMMAND MatrixTests)

# Add the test executable for Rational tests
add_executable(RationalTests tests/rational_test.cpp
        src/typing/number.cpp
        src/typing/number.h
        src/typing/rational.cpp
        src/typing/rational.h)

# Link Google Test and the library to the Rational test executable
target_link_libraries(RationalTests PRIVATE gtest gtest_main mathlib)

# Add a test for Rational
add_test(NAME RationalTests COMMAND RationalTests)

add_executable(StringTests tests/string_test.cpp
        src/typing/number.cpp
        src/typing/number.h
        src/typing/string.cpp
        src/typing/string.h)

# Link Google Test and the library to the String test executable
target_link_libraries(StringTests PRIVATE gtest gtest_main mathlib)

# Add a test for String
add_test(NAME StringTests COMMAND StringTests)


add_executable(LexerTests tests/lexer_test.cpp
        src/typing/number.cpp
        src/typing/number.h
        src/base/lexer.h)

# Link Google Test and the library to the Lexer test executable
target_link_libraries(LexerTests PRIVATE gtest gtest_main mathlib)

# Add a test for Lexer
add_test(NAME LexerTests COMMAND LexerTests)

add_executable(HistoryTests tests/history_test.cpp
        src/base/history.h
        src/base/history.cpp
)

# Link Google Test and the library to the History test executable
target_link_libraries(HistoryTests PRIVATE gtest gtest_main mathlib)

# Add a test for History
add_test(NAME HistoryTests COMMAND HistoryTests)