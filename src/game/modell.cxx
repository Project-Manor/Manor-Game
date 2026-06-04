#include "modell.hxx"

Modell::Modell() {
    _initModel(
        "res/models/glow_mouse.obj",
        "res/models/glow_mouse.png",
        "src/shaders/test.fs"
    );
}