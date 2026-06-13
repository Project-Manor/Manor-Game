#include "input.hxx"
#include <raylib.h>

namespace input {
    const bool pressed(const std::vector<int> action) {
        for (const int &i : action) {
            if (IsKeyPressed(i))
                return true;
        }
        return false;
    }

    const bool released(const std::vector<int> action) {
        for (const int &i : action) {
            if (IsKeyReleased(i))
                return true;
        }
        return false;
    }

    const bool held(const std::vector<int> action) {
        for (const int &i : action) {
            if (IsKeyDown(i))
                return true;
        }
        return false;
    }

    const bool free(const std::vector<int> action) {
        for (const int &i : action) {
            if (IsKeyUp(i)) continue;
            return false;
        }
        return true;
    }
}