# CMake generated Testfile for 
# Source directory: C:/repo/math-interpreter/MathImp
# Build directory: C:/repo/math-interpreter/MathImp/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[VectorTests]=] "C:/repo/math-interpreter/MathImp/cmake-build-debug/VectorTests.exe")
set_tests_properties([=[VectorTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/repo/math-interpreter/MathImp/CMakeLists.txt;63;add_test;C:/repo/math-interpreter/MathImp/CMakeLists.txt;0;")
add_test([=[MatrixTests]=] "C:/repo/math-interpreter/MathImp/cmake-build-debug/MatrixTests.exe")
set_tests_properties([=[MatrixTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/repo/math-interpreter/MathImp/CMakeLists.txt;78;add_test;C:/repo/math-interpreter/MathImp/CMakeLists.txt;0;")
add_test([=[RationalTests]=] "C:/repo/math-interpreter/MathImp/cmake-build-debug/RationalTests.exe")
set_tests_properties([=[RationalTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/repo/math-interpreter/MathImp/CMakeLists.txt;91;add_test;C:/repo/math-interpreter/MathImp/CMakeLists.txt;0;")
add_test([=[StringTests]=] "C:/repo/math-interpreter/MathImp/cmake-build-debug/StringTests.exe")
set_tests_properties([=[StringTests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/repo/math-interpreter/MathImp/CMakeLists.txt;103;add_test;C:/repo/math-interpreter/MathImp/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
