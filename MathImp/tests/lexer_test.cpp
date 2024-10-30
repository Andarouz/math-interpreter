#include <gtest/gtest.h>
#include "../src/base/lexer.h"

API_MI_BEGIN

TEST(LexerTest, TokenizeTypeVariable) {
    Lexer lexer;
    const std::string input = "int";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::TYPE_VARIABLE);
    EXPECT_EQ(tokens[0].value, "int");
}

TEST(LexerTest, TokenizeNameVariable) {
    Lexer lexer;
    const std::string input = "x";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::NAME_VARIABLE);
    EXPECT_EQ(tokens[0].value, "x");
}

TEST(LexerTest, TokenizeOperator) {
    Lexer lexer;
    const std::string input = "=";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[0].value, "=");
}

TEST(LexerTest, TokenizeValue) {
    Lexer lexer;
    const std::string input = "2";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::VALUE);
    EXPECT_EQ(tokens[0].value, "2");
}

TEST(LexerTest, TokenizeEndLine) {
    Lexer lexer;
    const std::string input = ";";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::OPERATOR); // Update if END_LINE type is added separately
    EXPECT_EQ(tokens[0].value, ";");
}

TEST(LexerTest, TokenizeComplexStatement) {
    Lexer lexer;
    const std::string input = "int x = 2;";
    const auto tokens = lexer.tokenize(input);
    ASSERT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[0].type, TokenType::TYPE_VARIABLE);
    EXPECT_EQ(tokens[0].value, "int");
    EXPECT_EQ(tokens[1].type, TokenType::NAME_VARIABLE);
    EXPECT_EQ(tokens[1].value, "x");
    EXPECT_EQ(tokens[2].type, TokenType::OPERATOR);
    EXPECT_EQ(tokens[2].value, "=");
    EXPECT_EQ(tokens[3].type, TokenType::VALUE);
    EXPECT_EQ(tokens[3].value, "2");
    EXPECT_EQ(tokens[4].type, TokenType::OPERATOR); // Update if END_LINE type is added
    EXPECT_EQ(tokens[4].value, ";");
}
//
// // Tests for error handling
// TEST(ErrorHandlerTest, InvalidVectorDeclaration) {
//     Lexer lexer;
//     const std::string input = "vec x = 2 ;";
//     std::vector<Lexer::Token> tokens = lexer.tokenize(input); // Tokenize the input
//
//     // Validate tokens to check for errors
//     lexer.validate(tokens);
//
//     // Check for error related to vector declaration
//     lexer.getErrorHandler().show_error_position(input);
//     // Here, you can check the output stream or any error reporting mechanism you have in place
//     // This is an example of how you might assert output in your testing framework
//     // EXPECT_STREQ(outputStream.str().c_str(), "Error message expected for vector declaration");
// }
//
// TEST(ErrorHandlerTest, InvalidIntegerDeclaration) {
//     Lexer lexer;
//     const std::string input = "int x = [12,4,];";
//     std::vector<Lexer::Token> tokens = lexer.tokenize(input); // Tokenize the input
//
//     // Validate tokens to check for errors
//     lexer.validate(tokens);
//
//     // Check for errors related to integer declaration and formatting
//     lexer.getErrorHandler().show_error_position(input);
//     // Similarly, assert the expected error output here
// }
//
// TEST(ErrorHandlerTest, UnmatchedBrackets) {
//     Lexer lexer;
//     const std::string input = "vec x = [1, 2, 3;";
//     std::vector<Lexer::Token> tokens = lexer.tokenize(input); // Tokenize the input
//
//     // Validate tokens to check for errors
//     lexer.validate(tokens);
//
//     // Check for unmatched opening bracket error
//     lexer.getErrorHandler().show_error_position(input);
//     // Assert the output or error reporting for unmatched brackets
// }
//
// TEST(ErrorHandlerTest, MissingSemicolon) {
//     Lexer lexer;
//     const std::string input = "int x = 42";
//     std::vector<Lexer::Token> tokens = lexer.tokenize(input); // Tokenize the input
//
//     // Validate tokens to check for errors
//     lexer.validate(tokens);
//
//     // Check for missing semicolon error
//     lexer.getErrorHandler().show_error_position(input);
//     // Assert the expected error message for missing semicolon
// }
API_MI_END