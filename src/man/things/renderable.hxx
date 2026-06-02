#pragma once
#include "../things/spatial.hxx"

namespace man::render {
    class Renderable : public things::Spatial {
    public:
        Renderable();
        virtual ~Renderable();

        virtual void draw();

    private:
        long long _renderIndex;
    };
}