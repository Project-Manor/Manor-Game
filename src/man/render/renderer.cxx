#include "renderer.hxx"
#include <raylib.h>

man::Renderer &man::Renderer::instance() {
    static Renderer inst;
    return inst;
}

const bool man::Renderer::isAlive() {
    return instance()._isAlive;
}

const int man::Renderer::getFPS() const {
    return GetFPS();
}

void man::Renderer::setFPS(int value) {
    SetTargetFPS(value);
}

man::Renderer::Renderer() :
    _isAlive(true)
{
    #ifndef DEBUG
        SetTraceLogLevel(LOG_NONE);
    #endif

    InitWindow(800, 450, "Manor Game");
    setFPS(60);
}

void man::Renderer::_proc() {
    if (WindowShouldClose()) {
        _term();
        return;
    }

    BeginDrawing();
    ClearBackground(SKYBLUE);
    EndDrawing();
}

void man::Renderer::_term() {
    CloseWindow();
    instance()._isAlive = false;
}