#pragma once
#include <string>
#include <raylib.h>
#include "ui_element.hxx"
#include "../../render/ui_renderable.hxx"

namespace man::things::ui {
    class UISprite : public UIElement, public render::UIRenderable {
    public:
        ~UISprite();
        void draw() override;

    protected:
        UIRenderable_initUIRenderableTemplate
        void _initUISprite(std::string texturePath);

    private:
        Texture2D _tex;
    };
}

#include "ui_sprite.t.hxx"