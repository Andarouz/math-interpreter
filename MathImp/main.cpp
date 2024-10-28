// #include <iostream>
// #include <string>
// #include <vector>
// #include <map>
// #include <fcntl.h>
// #include <sstream>
// #include <regex>
//
// #ifdef _WIN32
//     #include <windows.h>  // Windows-specific library
// #else
//     #include <termios.h>  // Linux and POSIX systems
// #endif
//
//
// #include "include/typing/number.h"
// #include "include/typing/vector.h"
//
// void splitString(const std::string& str,
//                  std::vector<std::string>& tokens,
//                  std::map<uint16_t, std::string>& history,
//                  std::map<std::string, std::string>& numbers
// ) {
//     std::istringstream stream(str);
//     std::string token;
//     const std::regex intRegex("^-?\\d+$"); // Regular expression to match integers
//
//     while (stream >> token) { // Используем поток для чтения по пробелам
//         if (std::regex_match(token, intRegex)) {
//             API_MI_NAMESPACE Number number(API_MI_NAMESPACE Variable(std::stoi(token)));
//             numbers.insert(std::pair<std::string, std::string>(token, number.dec()));
//             tokens.push_back(number.dec());
//         } else {
//             tokens.push_back(token);
//         }
//     }
//
//     history.insert(std::pair<uint16_t, std::string>(history.size(), str));
// }
//
// void printing_output(const std::vector<std::string>& charVector){
//     for (const auto& ch : charVector) {
//         std::cout << ch << ' ';
//     }
//
// }
// void removeSpaces(std::string& str) {
//     std::erase_if(str, [](char ch) {
//         return std::isspace(static_cast<unsigned char>(ch)); // Проверка на пробел
//     });
// }
// void clear(std::vector<std::string>& charVector) {
//     if(!charVector.empty())
//         charVector.clear();
// }
//
// int main() {
//     const std::vector numbers1 = {API_MI_NAMESPACE Number(API_MI_NAMESPACE Variable (56)), API_MI_NAMESPACE Number(API_MI_NAMESPACE Variable (24)), API_MI_NAMESPACE Number(API_MI_NAMESPACE Variable (2.5f))};
//     const API_MI_NAMESPACE Vector vec1(numbers1);
//     std::for_each(vec1.cbegin(), vec1.cend(), [](const API_MI_NAMESPACE Number& number) {
//         std::cout << number.hex() << ' ';
//     });
//     //
//     // std::map<uint16_t, std::string> history;
//     // std::map<std::string, std::string> numbers;
//     // std::map<std::string, std::string> vectors;
//     // std::map<std::string, std::string> matrix;
//     // std::vector<std::string> charVector1, charVector2, charVector3;
//     //
//     // std::string input;
//     // while(true) {
//     //     std::cout<< ">>> ";
//     //     std::getline(std::cin, input); // Считываем всю строку
//     //     if (input == "exit") {
//     //         break;
//     //     }
//     //
//     //     if(input == "history"){
//     //         for (const auto& [key, value] : history) {
//     //             std::cout << key << ": " << value << std::endl;
//     //         }
//     //         continue;
//     //     }
//     //
//     //     if(input == "numbers"){
//     //         for (const auto& [key, value] : numbers) {
//     //             std::cout << key << ": " << value << std::endl;
//     //         }
//     //         continue;
//     //     }
//     //     if (input == "get number") {
//     //         std::cout << "Enter the number key: ";
//     //         std::string key;
//     //         std::getline(std::cin, key);
//     //         if (auto it = numbers.find(key); it != numbers.end()) {
//     //             std::cout << "Value: " << it->second << std::endl;
//     //         } else {
//     //             std::cout << "Number not found." << std::endl;
//     //         }
//     //         continue;
//     //     }
//     //     // removeSpaces(input);
//     //     splitString(input, charVector1, history, numbers);
//     //     printing_output(charVector1);
//     //     clear(charVector1);
//     //     std::cout << std::endl;
//     //
//     // }
//     // return 0;
// }
#include <iostream>
#include <string>
#include "include/base/interpreter.h"

int main() {
    API_MI_NAMESPACE Interpreter interpreter;
    std::string input;

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        try {
            API_MI_NAMESPACE Variable result = interpreter.evaluate(input);
            std::cout << "Result: " << result.toString() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}