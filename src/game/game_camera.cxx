#include "game_camera.hxx"
#include "../man/things/things.hxx"
#include "../man/render/renderer.hxx"
#include "../man/time.hxx"
#include "player.hxx"
#include "raylib.h"
#include "raymath.h"

GameCamera::GameCamera() :
    _cursorEnabled(false),
    _activeMode(_mode::FOLLOW),
    _debugSpeed(3),
    _debugSensitivity(7),
    _followOffset({0, 1.0f, 4})
{
    _addProc(this, &GameCamera::_process);
}

void GameCamera::_process() {
#ifdef DEBUG
    if (IsKeyPressed(KEY_C)) {
        if (_activeMode != _mode::DEBUGFP) {
            _activeMode = _mode::DEBUGFP;
        }
        else {
            _activeMode = _mode::FOLLOW;
        }
    }
#endif

    switch (_activeMode) {
        case _mode::DEBUGFP:
            _debugFP();
            break;
        case _mode::FOLLOW:
            _follow();
            break;
    }
}

void GameCamera::_debugFP() {
    if (_cursorEnabled) {
        DisableCursor();
        _cursorEnabled = false;
    }

    Vector2 inputVec = {};
    if (IsKeyDown(KEY_U)) inputVec.y--;
    if (IsKeyDown(KEY_J)) inputVec.y++;
    if (IsKeyDown(KEY_H)) inputVec.x--;
    if (IsKeyDown(KEY_K)) inputVec.x++;
    Vector2 moveVec = Vector2Normalize(inputVec);

    Vector3 curPos = man::render::Renderer::instance().getPos();
    Vector3 movement = Vector3Normalize(man::render::Renderer::getCamX() * Vector3(1, 0, 1)) * moveVec.x - Vector3Normalize(man::render::Renderer::getCamZ() * Vector3(1, 0, 1)) * moveVec.y;
    man::render::Renderer::instance().setPos(curPos + movement * _debugSpeed * man::Time::deltaTime());

    Vector2 mouseMovement = GetMouseDelta();
    Vector3 curRot = man::render::Renderer::instance().getRot();
    man::render::Renderer::instance().setRot({
        curRot.x - (float)mouseMovement.y * _debugSensitivity * man::Time::deltaTime(),
        curRot.y - (float)mouseMovement.x * _debugSensitivity * man::Time::deltaTime(),
        0
    });
}

void GameCamera::_follow() {
    if (!_cursorEnabled) {
        EnableCursor();
        _cursorEnabled = true;
    }

    if (
        auto player = man::Things::getTagged<Player>("player");
        player
    ) {
        man::render::Renderer::setPos(Vector3Add(
            player->getPos(),
            _followOffset));
        man::render::Renderer::setRot({0, 0, 0});
    }
}