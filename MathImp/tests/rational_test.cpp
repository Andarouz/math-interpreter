#include "../include/typing/rational.h"
#include <gtest/gtest.h>
#include <stdexcept>


API_MI_BEGIN

TEST(RationalTest, DefaultConstructor) {
    Rational r;
    EXPECT_EQ(r.getNumerator(), 0);
    EXPECT_EQ(r.getDenominator(), 1);
}

TEST(RationalTest, ParameterizedConstructor) {
    Rational r(3, 4);
    EXPECT_EQ(r.getNumerator(), 3);
    EXPECT_EQ(r.getDenominator(), 4);
}

TEST(RationalTest, ZeroDenominatorThrows) {
    EXPECT_THROW(Rational(1, 0), std::invalid_argument);
}

TEST(RationalTest, CopyConstructor) {
    Rational r1(3, 4);
    Rational r2(r1);
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 4);
}

TEST(RationalTest, MoveConstructor) {
    Rational r1(3, 4);
    Rational r2(std::move(r1));
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 4);
}

TEST(RationalTest, AssignmentOperator) {
    Rational r1(3, 4);
    Rational r2;
    r2 = r1;
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 4);
}

TEST(RationalTest, MoveAssignmentOperator) {
    Rational r1(3, 4);
    Rational r2;
    r2 = std::move(r1);
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 4);
}

TEST(RationalTest, EqualityOperator) {
    Rational r1(3, 4);
    Rational r2(3, 4);
    EXPECT_TRUE(r1 == r2);
}

TEST(RationalTest, InequalityOperator) {
    Rational r1(3, 4);
    Rational r2(4, 5);
    EXPECT_TRUE(r1 != r2);
}

TEST(RationalTest, AdditionOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 + r2;
    EXPECT_EQ(r3.getNumerator(), 5);
    EXPECT_EQ(r3.getDenominator(), 6);
}

TEST(RationalTest, SubtractionOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 - r2;
    EXPECT_EQ(r3.getNumerator(), 1);
    EXPECT_EQ(r3.getDenominator(), 6);
}

TEST(RationalTest, MultiplicationOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 * r2;
    EXPECT_EQ(r3.getNumerator(), 1);
    EXPECT_EQ(r3.getDenominator(), 6);
}

TEST(RationalTest, DivisionOperator) {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 / r2;
    EXPECT_EQ(r3.getNumerator(), 3);
    EXPECT_EQ(r3.getDenominator(), 2);
}

TEST(RationalTest, DivisionByZeroThrows) {
    Rational r1(1, 2);
    Rational r2(0, 1);
    EXPECT_THROW(r1 / r2, std::invalid_argument);
}

TEST(RationalTest, IncrementOperators) {
    Rational r(1, 2);
    ++r;
    EXPECT_EQ(r.getNumerator(), 3);
    EXPECT_EQ(r.getDenominator(), 2);
    r++;
    EXPECT_EQ(r.getNumerator(), 5);
    EXPECT_EQ(r.getDenominator(), 2);
}

TEST(RationalTest, DecrementOperators) {
    Rational r(3, 2);
    --r;
    EXPECT_EQ(r.getNumerator(), 1);
    EXPECT_EQ(r.getDenominator(), 2);
    r--;
    EXPECT_EQ(r.getNumerator(), -1);
    EXPECT_EQ(r.getDenominator(), 2);
}

TEST(RationalTest, HexRepresentation) {
    Rational r(10, 15);
    EXPECT_EQ(r.hex(), "a/f");
}

TEST(RationalTest, DecRepresentation) {
    Rational r(10, 15);
    EXPECT_EQ(r.dec(), "10/15");
}

TEST(RationalTest, OctRepresentation) {
    Rational r(10, 15);
    EXPECT_EQ(r.oct(), "12/17");
}

TEST(RationalTest, BinRepresentation) {
    Rational r(10, 15);
    EXPECT_EQ(r.bin(), "00000000000000000000000000001010/00000000000000000000000000001111");
}

API_MI_END