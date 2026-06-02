#include "renderable.hxx"
#include "../render/renderer.hxx"

namespace man::render {
    Renderable::Renderable() :
        _renderIndex(Renderer::addRenderable(this))
    {}

    void Renderable::draw() {}

    Renderable::~Renderable() {
        Renderer::removeRenderable(_renderIndex);
    }
}