#pragma once
#include "../man/things/thing.hxx"
#include <raylib.h> //agel brakes

class GameCamera : public man::things::Thing {
public:
    GameCamera();
private:
    void _process();
    void _debugFP();
    void _follow();

    enum class _mode {
        DEBUGFP,
        FOLLOW
    };

    _mode _activeMode;
    bool _cursorEnabled;

    // Debug FP specific
    const int _debugSpeed;
    const float _debugSensitivity;

    // Follow specific
    const Vector3 _followOffset;
};
