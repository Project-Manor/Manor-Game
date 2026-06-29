#pragma once
#include <vector>
#include <raylib.h>

namespace input {
    #define ACTION(name, ...) \
    static const std::vector<int> name { __VA_ARGS__ };

    namespace move {
        ACTION(Up, KEY_W, KEY_UP)
        ACTION(Down, KEY_S, KEY_DOWN)
        ACTION(Left, KEY_A, KEY_LEFT)
        ACTION(Right, KEY_D, KEY_RIGHT)
    }

    namespace ui {
        ACTION(DockNerdy, KEY_F3)
    }
}