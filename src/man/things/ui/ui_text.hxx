#pragma once
#include <string>
#include "ui_element.hxx"
#include "../../render/ui_renderable.hxx"

namespace man::things::ui {
    class UIText : public UIElement, public render::UIRenderable {
    public:
        ~UIText();
        void draw() override;

    protected:
        UIRenderable_initUIRenderableTemplate
        void _initUIText (
            std::string str = "parasite",
            float fontSize = 64,
            float spacing = 5,
            Color clr = WHITE,
            std::string fontPath = "parasite"
        );

    private:
        std::string _str;
        float _fontSize;
        float _spacing;
        Color _clr;
        Font _font;
        bool _isFontDefault;
    };
}

#include "ui_text.t.hxx"