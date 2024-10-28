//
// Created by massonskyi on 25.10.24.
//

#ifndef ABSTRACTOBJECT_HPP
#define ABSTRACTOBJECT_HPP
#include <string>
#include "../core.hpp"

API_MI_BEGIN
class AbstractObject {

public API_VIRTUAL_METHODS:
    API_MI_ virtual ~AbstractObject() = default;

    [[nodiscard]]
    API_MI_ inline virtual std::string hex() const = 0;

    [[nodiscard]]
    API_MI_ inline virtual std::string dec() const = 0;

    [[nodiscard]]
    API_MI_ inline virtual std::string oct() const = 0;

    [[nodiscard]]
    API_MI_ inline virtual std::string bin() const = 0;


};

API_MI_END
#endif //ABSTRACTOBJECT_HPP
