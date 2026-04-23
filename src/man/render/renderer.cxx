#include "renderer.hxx"
#include <raylib.h>
#include "renderable.hxx"

namespace man::render {
    Renderer &Renderer::instance() {
        static Renderer inst;
        return inst;
    }

    const bool Renderer::isAlive() {
        return instance()._isAlive;
    }

    const int Renderer::getFPS() {
        return GetFPS();
    }

    void Renderer::setFPS(int value) {
        SetTargetFPS(value);
    }

    Renderer::Renderer() :
        _isAlive(true),
        _nextRenderIndex(0),
        _renders({})
    {
        #ifndef DEBUG
            SetTraceLogLevel(LOG_NONE);
        #endif

        InitWindow(800, 450, "Manor Game");
        setFPS(60);
    }

    void Renderer::_proc() {
        if (WindowShouldClose()) {
            _term();
            return;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        for (auto &[index, render] : _renders)
            render->draw();

        EndDrawing();
    }

    const RenderIndex Renderer::addRenderable(Renderable *render) {
        Renderer &inst = instance();
        inst._renders.emplace(inst._nextRenderIndex, render);
        return inst._nextRenderIndex++;
    }

    void Renderer::removeRenderable(const RenderIndex renderIndex) {
        instance()._renders.erase(renderIndex);
    }

    void Renderer::_term() {
        CloseWindow();
        instance()._isAlive = false;
    }
}