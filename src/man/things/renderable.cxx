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

    void Renderable::draw() {
        if (_draw) _draw.value()();
    }

    Renderable::~Renderable() {
        Renderer::removeRenderable(_renderIndex);
    }
}