//
// Created by massonskyi on 25.10.24.
//

#ifndef CORE_HPP
#define CORE_HPP

#define CORE_VERSION_MAJOR 0
#define CORE_VERSION_MINOR 1

#define API_MI_
#define API_MI_BEGIN namespace api_math_interpreter {
#define API_MI_END }
#define API_MI_NAMESPACE ::api_math_interpreter::

#define API_METHODS
#define API_VARIABLES
#define API_VIRTUAL_METHODS
#define API_CONSTS

API_MI_BEGIN

API_MI_ constexpr char RESERVED_WORDS[] = "int float str vec mat rat";
API_MI_ constexpr char RESERVED_OPERATORS[] = "+ - * / ^ = ; , [ ] /";


API_MI_END
#endif //CORE_HPP
