#include "core.hxx"
#include <raylib.h>

void man::init() {
    InitWindow(800, 450, "Manor Game");
    SetTargetFPS(60);
}

bool man::proc() {
    if (WindowShouldClose()) return false;
    BeginDrawing();

    ClearBackground(SKYBLUE);

    EndDrawing();
    return true;
}

void man::term() { CloseWindow(); }