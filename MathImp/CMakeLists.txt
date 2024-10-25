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
        include/typing/Variable.cpp
        include/typing/Variable.h
)

# Add the executable target
add_executable(MathImp main.cpp )

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

# Add the test executable
add_executable(VectorTests tests/vector_test.cpp
        include/typing/number.cpp
        include/typing/number.h
        include/typing/vector.cpp
        include/typing/vector.h)

# Link Google Test and the library to the test executable
target_link_libraries(VectorTests PRIVATE gtest gtest_main mathlib)

# Add a test
add_test(NAME VectorTests COMMAND VectorTests)