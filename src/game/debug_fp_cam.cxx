#include "debug_fp_cam.hxx"
#include "../man/render/renderer.hxx"
#include "../man/time.hxx"
#include "raylib.h"
#include "raymath.h"

DebugFPCamera::DebugFPCamera() :
    _speed(3),
    _sensitivity(7.0f),
    _isActive(false),
    _cursorEnabled(false)
{
    _addProc(this, &DebugFPCamera::_process);
}

void DebugFPCamera::_process() {
    if (IsKeyPressed(KEY_C)) {
        _isActive = !_isActive;
    }

    if (!_isActive) {
        if (!_cursorEnabled) {
            EnableCursor();
            _cursorEnabled = true;
        }
        return;
    }

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
    man::render::Renderer::instance().setPos(curPos + movement * _speed * man::Time::deltaTime());

    Vector2 mouseMovement = GetMouseDelta();
    Vector3 curRot = man::render::Renderer::instance().getRot();
    man::render::Renderer::instance().setRot({
        curRot.x - (float)mouseMovement.y * _sensitivity * man::Time::deltaTime(),
        curRot.y - (float)mouseMovement.x * _sensitivity * man::Time::deltaTime(),
        0
    });
}