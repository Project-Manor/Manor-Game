#include "renderable.hxx"
#include "../render/renderer.hxx"

namespace man::render {
    Renderable::Renderable() :
        _renderIndex(Renderer::addRenderable(this)),
        _draw(std::nullopt)
    {}

    Renderable::Renderable(std::function<void()> draw) :
        _renderIndex(Renderer::addRenderable(this)),
        _draw(draw)
    {}

    void Renderable::performDraw() {
        if (!isActive()) return;
        _draw ? _draw.value()() : draw();
    }

    void Renderable::draw() {}

    Renderable::~Renderable() {
        Renderer::removeRenderable(_renderIndex);
    }
}