#pragma once
#include "i_ui_element.hxx"
#include "../../../render/ui_renderable.hxx"
#include <string>
#include <raylib.h>

namespace man::iui {
    class IUISprite :
        public iui::IUIElement,
        public render::UIRenderable
    {
    public:
        ~IUISprite();
        void draw() override;

    protected:
        UIRenderable_initUIRenderableTemplate
        void _initUISprite(std::string texturePath);

        const Vector2 _getTextureSize();
        void _updateElementSize() override;

    private:
        Texture2D _tex;
    };
}

#include "i_ui_sprite.t.hxx"