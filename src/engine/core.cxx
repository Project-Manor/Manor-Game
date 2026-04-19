#include "core.hxx"
#include <raylib.h>

void engine::init() {
    InitWindow(800, 450, "Manor Game");
    SetTargetFPS(60);
}

bool engine::proc() {
    if (WindowShouldClose()) return false;

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return true;
}

void engine::term() { CloseWindow(); }