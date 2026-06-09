#include "ui_renderable.hxx"
#include "renderer.hxx"

namespace man::render {
    UIRenderable::UIRenderable() :
        _isInitialized(false),
        _renderLayer(0)
    {}

    UIRenderable::~UIRenderable() {
        if (!_isInitialized) return;
        Renderer::removeUIRenderable(_renderLayer, this);
    }

    void UIRenderable::_initUIRenderable2() {
        Renderer::addUIRenderable(_renderLayer, this);
    }
}