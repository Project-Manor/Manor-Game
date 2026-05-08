#include "player.hxx"
#include "../man/time.hxx"
#include "raymath.h"

Player::Player() :
    // Movement
    _speed(8),
    _deceleration(3),
    _currentSpeed(0),
    _lastMoveVec({})
{
    _addProc(this, &Player::_process);

    _pixelPerfectPosition = true;

    man::things::Sprite::addAnimation({
        "idle",
        "res/spritesheets/detective_idle.png",
        {0}
    });
    man::things::Sprite::addAnimation({
        "walk",
        "res/spritesheets/detective_walk.png",
        {2, 5}
    });
}

void Player::_process() {
    Vector3 inputVec = {};
    if (IsKeyDown(KEY_W)) inputVec.z--;
    if (IsKeyDown(KEY_S)) inputVec.z++;
    if (IsKeyDown(KEY_A)) inputVec.x--;
    if (IsKeyDown(KEY_D)) inputVec.x++;
    Vector3 moveVec = Vector3Normalize(inputVec);
    if (man::things::Sprite::getAnimation() == "walk" && Vector3Length(moveVec) == 0)
        moveVec = _lastMoveVec;
    else
        _lastMoveVec = moveVec;

    if (moveVec.x < 0) man::things::Sprite::flipSprite(true);
    if (moveVec.x > 0) man::things::Sprite::flipSprite(false);
    if (Vector3Length(inputVec) > 0) {
        man::things::Sprite::playAnimation("walk");
        _currentSpeed = _speed;
    }
    else {
        man::things::Sprite::playAnimation("idle");
        _currentSpeed = Clamp(_currentSpeed - _deceleration * man::Time::deltaTime(), 0, _speed);
    }

    Vector3 movement = moveVec * _currentSpeed / 16 * man::Time::deltaTime();

    _pos += movement;
}