#pragma once
#include "../man/things/thing.hxx"

class DebugFPCamera : public man::things::Thing {
    public:
        DebugFPCamera();

    private:
        void _process();

        const int _speed;
        const float _sensitivity;
        bool _isActive;
        bool _cursorEnabled;
};