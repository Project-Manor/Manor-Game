#pragma once
#include "../man/things/sprite.hxx"
#include <raylib.h>

class Player : public man::things::Sprite {
public:
    Player();

private:
    void _process();

    const int _speed;
    Vector3 _lastMoveVec;
};