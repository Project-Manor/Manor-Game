#pragma once
#include "../thing.hxx"
#include <functional>
#include <optional>

namespace man::things::ui {
    class Renderable : public Thing {
    public:
        Renderable(std::size_t renderLayer);

        Renderable (
            std::size_t renderLayer,
            std::function<void()> draw
        );

        ~Renderable();

        void performDraw();
        virtual void draw();

    private:
        int _renderLayer;
        std::optional<std::function<void()>> _draw;
    };
}