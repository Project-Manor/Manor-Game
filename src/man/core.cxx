#include "core.hxx"
#include <raylib.h>
#include "time.hxx"
#include "render/renderer.hxx"
#include "things/things.hxx"

void man::init() {
    Time::instance();
    render::Renderer::instance();
    man::Things::instance();
}

bool man::proc() {
    Time::instance()._proc();
    man::Things::instance()._proc();
    render::Renderer::instance()._proc();
    return render::Renderer::isAlive();
}

void man::term() {}