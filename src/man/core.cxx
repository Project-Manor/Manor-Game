#include "core.hxx"
#include <raylib.h>
#include "time.hxx"
#include "render/renderer.hxx"
#include "things/root_thing.hxx"

void man::init() {
    Time::instance();
    render::Renderer::instance();
    things::RootThing::instance();
}

bool man::proc() {
    things::RootThing::process();
    render::Renderer::instance()._proc();
    Time::instance()._proc();
    return render::Renderer::isAlive();
}

void man::term() {
    things::RootThing::terminate();
}