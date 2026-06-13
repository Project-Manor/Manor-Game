#pragma once
#include <vector>

namespace input {
    const bool pressed(const std::vector<int> action);
    const bool released(const std::vector<int> action);
    const bool held(const std::vector<int> action);
    const bool free(const std::vector<int> action);
};