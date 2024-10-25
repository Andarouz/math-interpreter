# CMake generated Testfile for 
# Source directory: /home/massonskyi/repo/math-interpretator-main/MathImp
# Build directory: /home/massonskyi/repo/math-interpretator-main/MathImp/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[VectorTests]=] "/home/massonskyi/repo/math-interpretator-main/MathImp/cmake-build-debug/VectorTests")
set_tests_properties([=[VectorTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;57;add_test;/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;0;")
add_test([=[MatrixTests]=] "/home/massonskyi/repo/math-interpretator-main/MathImp/cmake-build-debug/MatrixTests")
set_tests_properties([=[MatrixTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;72;add_test;/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;0;")
add_test([=[RationalTests]=] "/home/massonskyi/repo/math-interpretator-main/MathImp/cmake-build-debug/RationalTests")
set_tests_properties([=[RationalTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;85;add_test;/home/massonskyi/repo/math-interpretator-main/MathImp/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
