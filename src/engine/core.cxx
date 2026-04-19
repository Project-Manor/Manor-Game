#include "core.hxx"
#include <raylib.h>

void engine::init() {
    InitWindow(800, 450, "Manor Game");
    SetTargetFPS(60);
}

bool engine::proc() {
    if (WindowShouldClose()) return false;
    BeginDrawing();

    ClearBackground(SKYBLUE);

    EndDrawing();
    return true;
}

void engine::term() { CloseWindow(); }