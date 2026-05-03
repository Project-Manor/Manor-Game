#pragma once
#include "../render/renderable.hxx"
#include "spatial.hxx"
#include <raylib.h>

namespace man::things {
    class Sprite : public Spatial, public man::render::Renderable {
    public:
        Sprite();
        void launch() override;
        void process() override;
        void finish() override;
        void draw() override;

    private:
        Texture2D _tex;
        Rectangle _texRec;
        int _lastFrameTick;
    };

}
