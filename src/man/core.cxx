#include "core.hxx"
#include <raylib.h>
#include "time.hxx"
#include "render/renderer.hxx"

void man::init() {
    Time::instance();
    Renderer::instance();
}

bool man::proc() {
    Time::instance()._proc();
    Renderer::instance()._proc();
    return Renderer::isAlive();
}

void man::term() {}