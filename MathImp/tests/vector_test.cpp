#include "../include/typing/number.h"
#include "../include/typing/vector.h"
#include <gtest/gtest.h>

API_MI_BEGIN
TEST(VectorTest, Constructor) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    const Vector vec(numbers);
    EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, CopyConstructor) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    const Vector vec1(numbers);
    const Vector& vec2(vec1);
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1, vec2);
}

TEST(VectorTest, MoveConstructor) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec1(numbers);
    const Vector vec2(std::move(vec1));
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1.size(), 0);
}

TEST(VectorTest, AssignmentOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    const Vector vec1(numbers1);
    Vector vec2(numbers2);
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1, vec2);
}

TEST(VectorTest, MoveAssignmentOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    Vector vec1(numbers1);
    Vector vec2(numbers2);
    vec2 = std::move(vec1);
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec1.size(), 0);
}

TEST(VectorTest, EqualityOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(1), Number(2), Number(3)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    EXPECT_TRUE(vec1 == vec2);
}

TEST(VectorTest, InequalityOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(VectorTest, AdditionOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    Vector result = vec1 + vec2;
    EXPECT_EQ(result[0], Number(5));
    EXPECT_EQ(result[1], Number(7));
    EXPECT_EQ(result[2], Number(9));
}

TEST(VectorTest, SubtractionOperator) {
    const std::vector<Number> numbers1 = {Number(4), Number(5), Number(6)};
    const std::vector<Number> numbers2 = {Number(1), Number(2), Number(3)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    Vector result = vec1 - vec2;
    EXPECT_EQ(result[0], Number(3));
    EXPECT_EQ(result[1], Number(3));
    EXPECT_EQ(result[2], Number(3));
}

TEST(VectorTest, MultiplicationOperator) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    Vector result = vec1 * vec2;
    EXPECT_EQ(result[0], Number(4));
    EXPECT_EQ(result[1], Number(10));
    EXPECT_EQ(result[2], Number(18));
}

TEST(VectorTest, DivisionOperator) {
    const std::vector<Number> numbers1 = {Number(4), Number(6), Number(8)};
    const std::vector<Number> numbers2 = {Number(2), Number(3), Number(4)};
    const Vector vec1(numbers1);
    const Vector vec2(numbers2);
    Vector result = vec1 / vec2;
    EXPECT_EQ(result[0], Number(2));
    EXPECT_EQ(result[1], Number(2));
    EXPECT_EQ(result[2], Number(2));
}

TEST(VectorTest, IndexOperator) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec(numbers);
    EXPECT_EQ(vec[0], Number(1));
    EXPECT_EQ(vec[1], Number(2));
    EXPECT_EQ(vec[2], Number(3));
}

TEST(VectorTest, Append) {
    Vector vec;
    vec.append(Number(1));
    vec.append(Number(2));
    vec.append(Number(3));
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], Number(1));
    EXPECT_EQ(vec[1], Number(2));
    EXPECT_EQ(vec[2], Number(3));
}

TEST(VectorTest, PopBack) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec(numbers);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], Number(1));
    EXPECT_EQ(vec[1], Number(2));
}

TEST(VectorTest, Clear) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec(numbers);
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, Erase) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec(numbers);
    vec.erase(1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], Number(1));
    EXPECT_EQ(vec[1], Number(3));
}

TEST(VectorTest, Insert) {
    const std::vector<Number> numbers = {Number(1), Number(3)};
    Vector vec(numbers);
    vec.insert(1, Number(2));
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], Number(1));
    EXPECT_EQ(vec[1], Number(2));
    EXPECT_EQ(vec[2], Number(3));
}

TEST(VectorTest, Resize) {
    const std::vector<Number> numbers = {Number(1), Number(2), Number(3)};
    Vector vec(numbers);
    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
}

TEST(VectorTest, Swap) {
    const std::vector<Number> numbers1 = {Number(1), Number(2), Number(3)};
    const std::vector<Number> numbers2 = {Number(4), Number(5), Number(6)};
    Vector vec1(numbers1);
    Vector vec2(numbers2);
    vec1.swap(vec2);
    EXPECT_EQ(vec1[0], Number(4));
    EXPECT_EQ(vec1[1], Number(5));
    EXPECT_EQ(vec1[2], Number(6));
    EXPECT_EQ(vec2[0], Number(1));
    EXPECT_EQ(vec2[1], Number(2));
    EXPECT_EQ(vec2[2], Number(3));
}
API_MI_END