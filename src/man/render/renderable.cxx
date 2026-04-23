#include "renderable.hxx"
#include "renderer.hxx"

namespace man::render {
    Renderable::Renderable() :
        _renderIndex(Renderer::addRenderable(this))
    {}

    void Renderable::draw() {}

    Renderable::~Renderable() {
        Renderer::removeRenderable(_renderIndex);
    }
}