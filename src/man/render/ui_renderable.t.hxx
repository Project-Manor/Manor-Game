#pragma once
#include "ui_renderable.hxx"

namespace man::render {
    UIRenderable_initUIRenderableTemplate
    void UIRenderable::_initUIRenderable() {
        _renderLayer = RenderLayer;
        _initUIRenderable2();
    }
}