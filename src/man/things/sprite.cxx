#include "sprite.hxx"
#include "../render/renderer.hxx"
#include "../time.hxx"

namespace man::things {
    Sprite::Sprite() :
        _tex(LoadTexture("res/spritesheets/detective_walk.png")),
        _texRec({0, 0, (float)_tex.width / 6, (float)_tex.height})
    {}

    void Sprite::launch() {

    }

    void Sprite::process() {

    }

    void Sprite::finish() {

    }

    void Sprite::draw() {

    }
}