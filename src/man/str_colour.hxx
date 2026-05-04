#pragma once
#include <string>

namespace man {
    std::string strColour (
        std::string ansiCode,
        std::string string
    );

    std::string strRed(std::string string);
    std::string strGreen(std::string string);
    std::string strYellow(std::string string);
    std::string strCyan(std::string string);
}