//
// Created by massonskyi on 28.10.24.
//
#include <gtest/gtest.h>
#include "../include/base/history.h"

API_MI_BEGIN

// TEST(HistoryTest, DefaultConstructor) {
//     const History history;
//     EXPECT_EQ(history.checkLength(), false);
// }
//
// TEST(HistoryTest, ParameterizedConstructor) {
//     const History history(10);
//     EXPECT_EQ(history.checkLength(), false);
// }

TEST(HistoryTest, AddCommand) {
    History history{999};
    history.add("command1");
    history.add("command2");
    const std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    history.show();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "0: command1\n1: command2\n");
}

TEST(HistoryTest, ShowWithCallback) {
    History history{999};
    history.add("command1");
    history.add("command2");
    std::vector<std::string> output;
    history.show(2, [&output](const uint16_t key, const std::string& value) {
        output.push_back(std::to_string(key) + ": " + value);
    });
    ASSERT_EQ(output.size(), 2);
    EXPECT_EQ(output[0], "1: command2");
    EXPECT_EQ(output[1], "0: command1");
}

TEST(HistoryTest, ClearHistory) {
    History history{999};
    history.add("command1");
    history.clear();
    const std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    history.show();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "");
}

TEST(HistoryTest, CheckLength) {
    History history(1);
    history.add("command1");
    history.add("command2");
    const std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    history.show();
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "0: command2\n");
}

API_MI_END