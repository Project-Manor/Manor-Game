#include "core.hxx"
#include <raylib.h>
#include "time.hxx"

void man::init() {
    Time::instance();

#ifndef DEBUG
    SetTraceLogLevel(LOG_NONE);
#endif

    InitWindow(800, 450, "Manor Game");
    setFPS(60);
}

bool man::proc() {
    Time::instance()._proc();

    if (WindowShouldClose()) return false;
    BeginDrawing();

    ClearBackground(SKYBLUE);

    EndDrawing();
    return true;
}

void man::term() { CloseWindow(); }

int man::getFPS() { return GetFPS(); }
void man::setFPS(int value) { SetTargetFPS(value); }