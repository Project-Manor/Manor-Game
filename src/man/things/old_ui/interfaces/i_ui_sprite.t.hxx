#pragma once
#include "i_ui_sprite.hxx"
#include <raylib.h>

namespace man::iui {
    UIRenderable_initUIRenderableTemplate
    void IUISprite::_initUISprite(std::string texturePath) {
        _initUIRenderable<RenderLayer>();
        _tex = LoadTexture(texturePath.c_str());
        _updateElementSize();
    }
}