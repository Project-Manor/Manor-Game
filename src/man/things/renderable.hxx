#pragma once
#include "../things/spatial.hxx"
#include <functional>
#include <optional>

namespace man::render {
    class Renderable : public things::Spatial {
    public:
        Renderable();
        Renderable(std::function<void()> draw);

        virtual ~Renderable();

        void performDraw();
        virtual void draw();

    private:
        long long _renderIndex;
        std::optional<std::function<void()>> _draw;
    };
}