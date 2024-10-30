//
// Created by massonskyi on 28.10.24.
//

#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <functional>
#include <map>
#include <string>

#include "../core.hpp"

API_MI_BEGIN

class History final {
public API_METHODS:
    History();
    explicit History(int length = 999);
    History(const History&) = delete;
    History(History&&) noexcept = delete;
    ~History() = default;

    API_MI_ void show() const;
    API_MI_ void show(int count, const std::function<void(uint16_t, const std::string&)>& callback) const;

    API_MI_ void show(int begin, int end, const std::function<void(uint16_t, const std::string&)>& callback) const;

    API_MI_ void show(const std::function<void(uint16_t, const std::string&)>& callback) const;

    API_MI_ void add(const std::string& command);

    API_MI_ void clear();

private API_METHODS:

    [[nodiscard]]
    API_MI_ bool checkLength() const;

private API_VARIABLES:
    int maxLength_;

    std::map<uint16_t, std::string> history_;
};

API_MI_END
#endif //HISTORY_HPP
