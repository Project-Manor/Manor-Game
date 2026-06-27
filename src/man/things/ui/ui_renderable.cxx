#include "ui_renderable.hxx"
#include "../../render/renderer.hxx"
#include <man>

namespace man::things::ui {
    Renderable::Renderable(std::size_t renderLayer) :
        _renderLayer(renderLayer),
        _draw(std::nullopt)
    {
        render::Renderer::addUIRenderable(_renderLayer, this);
    }

    Renderable::Renderable (
        std::size_t renderLayer,
        std::function<void()> draw
    ) :
        _renderLayer(renderLayer),
        _draw(draw)
    {
        render::Renderer::addUIRenderable(_renderLayer, this);
    }

    Renderable::~Renderable() {
        render::Renderer::removeUIRenderable(_renderLayer, this);
    }

    void Renderable::draw() {
        if (_draw) _draw.value()();
    }
}