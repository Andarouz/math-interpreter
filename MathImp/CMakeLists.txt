cmake_minimum_required(VERSION 3.29)
project(MathImp)

set(CMAKE_CXX_STANDARD 20)

# Add the library target
add_library(mathlib STATIC
        include/typing/number.cpp
        include/typing/number.h
        include/core.hpp
        include/typing/AbstractObject.hpp
        include/typing/vector.cpp
        include/typing/vector.h
        tests/vector_test.cpp
        include/typing/variable.cpp
        include/typing/variable.h
        include/typing/matrix.cpp
        include/typing/matrix.h
        tests/matrix_test.cpp
        include/typing/rational.cpp
        include/typing/rational.h
        tests/rational_test.cpp
)

# Add the executable target
add_executable(MathImp main.cpp)

# Link the library to the executable
target_link_libraries(MathImp PRIVATE mathlib)

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
        include/typing/number.cpp
        include/typing/number.h
        include/typing/vector.cpp
        include/typing/vector.h)

# Link Google Test and the library to the Vector test executable
target_link_libraries(VectorTests PRIVATE gtest gtest_main mathlib)

# Add a test for Vector
add_test(NAME VectorTests COMMAND VectorTests)

# Add the test executable for Matrix tests
add_executable(MatrixTests tests/matrix_test.cpp
        include/typing/number.cpp
        include/typing/number.h
        include/typing/vector.cpp
        include/typing/vector.h
        include/typing/matrix.cpp
        include/typing/matrix.h)

# Link Google Test and the library to the Matrix test executable
target_link_libraries(MatrixTests PRIVATE gtest gtest_main mathlib)

# Add a test for Matrix
add_test(NAME MatrixTests COMMAND MatrixTests)

# Add the test executable for Rational tests
add_executable(RationalTests tests/rational_test.cpp
        include/typing/number.cpp
        include/typing/number.h
        include/typing/rational.cpp
        include/typing/rational.h)

# Link Google Test and the library to the Rational test executable
target_link_libraries(RationalTests PRIVATE gtest gtest_main mathlib)

# Add a test for Rational
add_test(NAME RationalTests COMMAND RationalTests)