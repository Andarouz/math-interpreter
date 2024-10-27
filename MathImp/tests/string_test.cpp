//
// Created by gavri on 27.10.2024.
//
#include <gtest/gtest.h>
#include "../include/typing/string.h"

API_MI_BEGIN

TEST(StringTest, DefaultConstructor) {
    const String str;
    EXPECT_EQ(str.size(), 0);
}

TEST(StringTest, ConstructorWithStdString) {
    const std::string testStr = "Hello";
    const String str(testStr);
    EXPECT_EQ(str.size(), testStr.size());
    EXPECT_EQ(str.hex(), "0x480x650x6c0x6c0x6f");
}

TEST(StringTest, ConstructorWithCString) {
    const auto testStr = "Hello";
    const String str(testStr);
    EXPECT_EQ(str.size(), strlen(testStr));
    EXPECT_EQ(str.hex(), "0x480x650x6c0x6c0x6f");
}

TEST(StringTest, CopyConstructor) {
    const String str1("Hello");
    const String& str2(str1);
    EXPECT_EQ(str1, str2);
}

TEST(StringTest, MoveConstructor) {
    String str1("Hello");
    const String str2(std::move(str1));
    EXPECT_EQ(str2, "Hello");
}

TEST(StringTest, HexConversion) {
    const String str("Hello");
    EXPECT_EQ(str.hex(), "0x480x650x6c0x6c0x6f");
}

TEST(StringTest, DecConversion) {
    const String str("Hello");
    EXPECT_EQ(str.dec(), "72101108108111");
}

TEST(StringTest, OctConversion) {
    const String str("Hello");
    EXPECT_EQ(str.oct(), "0110100140150140157");
}

TEST(StringTest, BinConversion) {
    const String str("Hello");
    EXPECT_EQ(str.bin(), "0100100001100101011011000110110001101111");
}

TEST(StringTest, EqualityOperator) {
    const String str1("Hello");
    const String str2("Hello");
    EXPECT_TRUE(str1 == str2);
    EXPECT_FALSE(str1 != str2);
}

TEST(StringTest, AdditionOperator) {
    const String str1("Hello");
    const String str2(" World");
    const String result = str1 + str2;
    EXPECT_EQ(result, "Hello World");
}

TEST(StringTest, Substring) {
    const String str("Hello World");
    const String substr = str.substring(0, 5);
    EXPECT_EQ(substr, "Hello");
}

TEST(StringTest, Trim) {
    const String str("  Hello World  ");
    const String trimmed = str.trim();
    EXPECT_EQ(trimmed, "Hello World");
}

TEST(StringTest, ToUpperCase) {
    const String str("Hello World");
    const String upper = str.toUpperCase();
    EXPECT_EQ(upper, "HELLO WORLD");
}

TEST(StringTest, ToLowerCase) {
    const String str("Hello World");
    const String lower = str.toLowerCase();
    EXPECT_EQ(lower, "hello world");
}

TEST(StringTest, Split) {
    const String str("Hello,World,Test");
    const std::vector<String> result = str.split(",");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
    EXPECT_EQ(result[2], "Test");
}
TEST(StringTest, Slice) {
    const String str("Hello World Test");
    const auto result = str.slice(0, 5);
    ASSERT_EQ(result.size(), 5);
    EXPECT_EQ(result, "Hello");
}

TEST(StringTest, Replace) {
    const String str("Hello World");
    const String replaced = str.replace("World", "Test");
    EXPECT_EQ(replaced, "Hello Test");
}

TEST(StringTest, IndexOf) {
    const String str("Hello World");
    const int index = str.indexOf("World");
    EXPECT_EQ(index, 6);
}

API_MI_END