#pragma once

namespace man {
    inline constexpr bool kDebug =
#ifdef DEBUG
        true;
#else
        false;
#endif

    void init();
    bool proc();
    void term();
}