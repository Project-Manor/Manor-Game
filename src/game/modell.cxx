#include "modell.hxx"

Modell::Modell() {
    _initModel(
        "res/models/glow_mouse/.obj",
        "res/models/white.png",
        "src/shaders/fog.fs",
        "src/shaders/fog.vs"
    );
}