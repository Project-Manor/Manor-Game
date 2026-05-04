#include "str_colour.hxx"
#include <format>

std::string man::strColour (
    std::string ansiCode,
    std::string string
) {
    return std::format("\033[{}m{}\033[0m", ansiCode, string);
}

#define FUNC(name, code)                    \
std::string man::name(std::string string)   \
{ return man::strColour(#code, string); }

FUNC(strRed, 31)
FUNC(strGreen, 32)
FUNC(strYellow, 33)
FUNC(strCyan, 36)