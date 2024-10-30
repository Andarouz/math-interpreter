#include "../src/typing/vector.h"
#include "../src/typing/number.h"
#include "../src/typing/matrix.h"
#include <gtest/gtest.h>

API_MI_BEGIN

TEST(MatrixTest, DefaultConstructor) {
    const Matrix matrix;
    EXPECT_EQ(matrix.size(), 0);
}

TEST(MatrixTest, VectorConstructor) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const Matrix matrix(vectors);
    EXPECT_EQ(matrix.size(), 2);
}

TEST(MatrixTest, CopyConstructor) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const Matrix matrix1(vectors);
    const Matrix& matrix2(matrix1);
    EXPECT_EQ(matrix2.size(), 2);
    EXPECT_EQ(matrix1, matrix2);
}

TEST(MatrixTest, MoveConstructor) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    Matrix matrix1(vectors);
    const Matrix matrix2(std::move(matrix1));
    EXPECT_EQ(matrix2.size(), 2);
    EXPECT_EQ(matrix1.size(), 0);
}

TEST(MatrixTest, AssignmentOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    const Matrix matrix1(vectors1);
    Matrix matrix2(vectors2);
    matrix2 = matrix1;
    EXPECT_EQ(matrix2.size(), 2);
    EXPECT_EQ(matrix1, matrix2);
}

TEST(MatrixTest, MoveAssignmentOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    Matrix matrix1(vectors1);
    Matrix matrix2(vectors2);
    matrix2 = std::move(matrix1);
    EXPECT_EQ(matrix2.size(), 2);
    EXPECT_EQ(matrix1.size(), 0);
}

TEST(MatrixTest, EqualityOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, InequalityOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    EXPECT_TRUE(matrix1 != matrix2);
}

TEST(MatrixTest, AdditionOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    Matrix result = matrix1 + matrix2;
    EXPECT_EQ(result[0][0], Number(6));
    EXPECT_EQ(result[0][1], Number(8));
    EXPECT_EQ(result[1][0], Number(10));
    EXPECT_EQ(result[1][1], Number(12));
}

TEST(MatrixTest, SubtractionOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    const std::vector<Vector> vectors2 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    Matrix result = matrix1 - matrix2;
    EXPECT_EQ(result[0][0], Number(4));
    EXPECT_EQ(result[0][1], Number(4));
    EXPECT_EQ(result[1][0], Number(4));
    EXPECT_EQ(result[1][1], Number(4));
}

TEST(MatrixTest, MultiplicationOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    const std::vector<Vector> vectors2 = {Vector({Number(5), Number(6)}), Vector({Number(7), Number(8)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    Matrix result = matrix1 * matrix2;
    EXPECT_EQ(result[0][0], Number(5));
    EXPECT_EQ(result[0][1], Number(12));
    EXPECT_EQ(result[1][0], Number(21));
    EXPECT_EQ(result[1][1], Number(32));
}

TEST(MatrixTest, DivisionOperator) {
    const std::vector<Vector> vectors1 = {Vector({Number(4), Number(6)}), Vector({Number(8), Number(10)})};
    const std::vector<Vector> vectors2 = {Vector({Number(2), Number(3)}), Vector({Number(4), Number(5)})};
    const Matrix matrix1(vectors1);
    const Matrix matrix2(vectors2);
    Matrix result = matrix1 / matrix2;
    EXPECT_EQ(result[0][0], Number(2));
    EXPECT_EQ(result[0][1], Number(2));
    EXPECT_EQ(result[1][0], Number(2));
    EXPECT_EQ(result[1][1], Number(2));
}

TEST(MatrixTest, Append) {
    Matrix matrix;
    const Vector vector({Number(1), Number(2)});
    matrix.append(vector);
    EXPECT_EQ(matrix.size(), 1);
    EXPECT_EQ(matrix[0], vector);
}

TEST(MatrixTest, PopBack) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    Matrix matrix(vectors);
    matrix.pop_back();
    EXPECT_EQ(matrix.size(), 1);
}

TEST(MatrixTest, Clear) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    Matrix matrix(vectors);
    matrix.clear();
    EXPECT_EQ(matrix.size(), 0);
}

TEST(MatrixTest, Erase) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)}), Vector({Number(3), Number(4)})};
    Matrix matrix(vectors);
    matrix.erase(0);
    EXPECT_EQ(matrix.size(), 1);
    EXPECT_EQ(matrix[0], Vector({Number(3), Number(4)}));
}

TEST(MatrixTest, Insert) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(3)})};
    Matrix matrix(vectors);
    matrix.insert(1, Vector({Number(2), Number(4)}));
    EXPECT_EQ(matrix.size(), 2);
    EXPECT_EQ(matrix[1], Vector({Number(2), Number(4)}));
}

TEST(MatrixTest, Resize) {
    const std::vector<Vector> vectors = {Vector({Number(1), Number(2)})};
    Matrix matrix(vectors);
    matrix.resize(3, 2);
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[2].size(), 2);
}

TEST(MatrixTest, Swap) {
    const std::vector<Vector> vectors1 = {Vector({Number(1), Number(2)})};
    const std::vector<Vector> vectors2 = {Vector({Number(3), Number(4)})};
    Matrix matrix1(vectors1);
    Matrix matrix2(vectors2);
    matrix1.swap(matrix2);
    EXPECT_EQ(matrix1[0], Vector({Number(3), Number(4)}));
    EXPECT_EQ(matrix2[0], Vector({Number(1), Number(2)}));
}

API_MI_END