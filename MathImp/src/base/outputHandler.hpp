//
// Created by massonskyi on 30.10.24.
//

#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP
#include <array>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include "../core.hpp"
#include <fmt/core.h>
API_MI_BEGIN
/**
 * @class OutputHandler
 * @brief A class for printing text with ANSI color codes.
 *
 * This class provides functionality to print text with various ANSI color codes.
 * It supports enabling/disabling color output, setting custom colors, and global formatting.
 */
class OutputHandler final{
public:
    /**
     * @enum Color
     * @brief Enumeration of ANSI color codes.
     *
     * This enum defines various ANSI color codes that can be used for text formatting.
     */
    enum class Color {
        Reset = 0,   ///< Reset color to default.
        Red = 31,    ///< Red color.
        Green = 32,  ///< Green color.
        Yellow = 33, ///< Yellow color.
        Blue = 34,   ///< Blue color.
        Magenta = 35,///< Magenta color.
        Cyan = 36,   ///< Cyan color.
        White = 37   ///< White color.
    };
    /**
     * @brief Constructor for OutputHandler.
     *
     * @param enable_color A boolean to enable or disable color output. Default is true.
     * @param global_format The format string to use globally.
     */
     explicit OutputHandler(const bool enable_color = true, const std::optional<std::string> &global_format = std::nullopt)
     : color_enabled(enable_color), global_format(global_format) {
      custom_color.fill(std::nullopt); ///<- Initialization array custom_color
     };

    /**
     * @brief Set whether color output is enabled.
     *
     * @param enabled A boolean to enable or disable color output.
     */
     void set_color_enabled(const bool enabled){
      color_enabled = enabled;
     };

    /**
     * @brief Set a custom color with a specific ANSI code.
     *
     * @param color The color to set.
     * @param code The ANSI code for the custom color.
     */
    void set_custom_color(Color color, const std::string& code){
        custom_color[static_cast<int>(color)] = code;
    };

    /**
     * @brief Set a global format for all printed text.
     *
     * @param format The format string to use globally.
     */
    void set_global_format(const std::string& format){
        global_format = format;
    };

    /**
     * @brief Print text with a specified color.
     *
     * @param text The text to print.
     * @param color The color to use for the text. Default is Color::Reset.
     */
    void print(const std::string& text, Color color = Color::Reset) const{
        if (color_enabled) {
            if (custom_color[static_cast<int>(color)]) {
                std::cout << "\033[" << custom_color[static_cast<int>(color)].value() << "m";
            } else {
                std::cout << "\033[" << static_cast<int>(color) << "m";
            }
        }
        if (global_format) {
            std::ostringstream oss;
            oss << global_format.value();
            const std::string formatted_text = oss.str();
            std::cout << formatted_text;
        } else {
            std::cout << text;
        }
        if (color_enabled) {
            std::cout << "\033[0m";
        }
    };
    /**
     * @brief Print an error message with red text.
     *
     * @param text The error message to print.
     */
    void err(const std::string &text) const{
        print(text, Color::Red);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void debug(const std::string &text) const{
        print(text, Color::Green);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void info(const std::string &text) const{
        print(text, Color::Blue);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void warn(const std::string &text) const{
        print(text, Color::Yellow);
    };
    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void success(const std::string &text) const{
        print(text, Color::Green);
    };
    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void critical(const std::string &text) const{
        print(text, Color::Red);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void fatal(const std::string &text) const{
        print(text, Color::Red);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @param text The text to print.
     */
    void trace(const std::string &text) const{
        print(text, Color::Cyan);
    };

    /**
     * @brief Print formatted text with a specified color.
     *
     * @tparam Args Variadic template for format arguments.
     * @param color The color to use for the text.
     * @param formatString The format string.
     * @param args The arguments for the format string.
     */

    template<typename... Args>
    void formatted(const Color color, std::string formatString, Args&&... args) const {
        std::string formattedMessage = fmt::format(formatString, std::forward<Args>(args)...);

        if (global_format.has_value()) {
            std::ostringstream global_oss;
            global_oss << fmt::format(global_format.value(), formattedMessage);
            const std::string globalFormattedMessage = global_oss.str();
            print(globalFormattedMessage, color);
        } else {
            print(formattedMessage, color);
        }
    }

private:
    bool color_enabled; ///< Boolean indicating if color output is enabled.
    std::optional<std::string> global_format; ///< Optional global format string.
    std::array<std::optional<std::string>, 256> custom_color; ///< Array of optional custom ANSI codes for colors.
};
API_MI_END
#endif //OUTPUTHANDLER_HPP
