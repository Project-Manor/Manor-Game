#pragma once
#include "ui_sprite.hxx"
#include <raylib.h>

namespace man::things::ui {
    UIRenderable_initUIRenderableTemplate
    void UISprite::_initUISprite(std::string texturePath) {
        _initUIRenderable<RenderLayer>();
        _tex = LoadTexture(texturePath.c_str());
        _setElementSize ({
            _tex.width,
            _tex.height
        });
    }
}