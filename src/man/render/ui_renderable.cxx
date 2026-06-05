#include "ui_renderable.hxx"
#include "renderer.hxx"

namespace man::render {
    UIRenderable::UIRenderable(const int renderLayer) :
        _renderLayer(renderLayer)
    {
        Renderer::addUIRenderable(_renderLayer, this);
    }

    UIRenderable::~UIRenderable() {
        Renderer::removeUIRenderable(_renderLayer, this);
    }
}