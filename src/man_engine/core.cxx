#include "core.hxx"
#include <raylib.h>
#include <print>
#include "time.hxx"

void man::init() {
    Time::instance();

    InitWindow(800, 450, "Manor Game");
    SetTargetFPS(60);
}

bool man::proc() {
    Time::instance()._time += 1;

    if (WindowShouldClose()) return false;
    BeginDrawing();

    ClearBackground(SKYBLUE);

    std::println("Time: {}", Time::time());

    EndDrawing();
    return true;
}

void man::term() { CloseWindow(); }