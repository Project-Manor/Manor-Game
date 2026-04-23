#pragma once
#include <unordered_map>
#include "../core.hxx"
#include "render_types.hxx"
#include "renderable.hxx"

namespace man::render {
    class Renderer {
    public:
        Renderer(const Renderer&) = delete;
        static Renderer &instance();
        static const bool isAlive();

        static const int getFPS();
        static void setFPS(int value);

        static const RenderIndex addRenderable(Renderable *render);
        static void removeRenderable(const RenderIndex renderIndex);

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();

        bool _isAlive;

        RenderIndex _nextRenderIndex;
        std::unordered_map <
            RenderIndex,
            Renderable*
        > _renders;
    };
}