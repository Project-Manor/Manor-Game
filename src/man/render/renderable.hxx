#pragma once
#include "render_types.hxx"

namespace man::render {
    class Renderable {
    public:
        Renderable();
        virtual ~Renderable();

        virtual void draw();

    private:
        RenderIndex _renderIndex;
    };
}