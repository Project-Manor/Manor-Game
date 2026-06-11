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
            Font font = GetFontDefault(),
            float fontSize = 64,
            float spacing = 5,
            Color clr = WHITE
        );

    private:
        std::string _str;
        Font _font;
        float _fontSize;
        float _spacing;
        Color _clr;
    };
}

#include "ui_text.t.hxx"