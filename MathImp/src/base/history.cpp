#include "history.h"

#include <iostream>

API_MI_BEGIN
    History::History() : maxLength_(999) {}

History::History(const int length) : maxLength_(length) {}

void History::show() const {
    std::for_each(history_.cbegin(), history_.cend(), [](const auto& pair) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    });
}

void History::show(const int count, const std::function<void(uint16_t, const std::string&)>& callback) const {
    if (count <= 0) return;
    auto it = history_.crbegin();
    for (int i = 0; i < count && it != history_.crend(); ++i, ++it) {
        callback(it->first, it->second);
    }
}

void History::show(const int begin, const int end, const std::function<void(uint16_t, const std::string&)>& callback) const {
    for (auto it = history_.cbegin(); it != history_.cend(); ++it) {
        if (it->first >= begin && it->first <= end) {
            callback(it->first, it->second);
        }
    }
}

void History::show(const std::function<void(uint16_t, const std::string&)>& callback) const {
    std::for_each(history_.cbegin(), history_.cend(), [&callback](const auto& pair) {
        callback(pair.first, pair.second);
    });
}

void History::add(const std::string& command) {
    if(checkLength()) {
        history_.erase(history_.begin());
    }
    history_.insert(std::pair<uint16_t, std::string>(history_.size(), command));
}

void History::clear() {
    history_.clear();
}

bool History::checkLength() const {
    return history_.size() >= maxLength_;
}

API_MI_END