#pragma once
#include "i_ui_element.hxx"
#include "../../../render/ui_renderable.hxx"
#include <string>

namespace man::iui {
    class IUIText :
        public IUIElement,
        public render::UIRenderable
    {
    public:
        ~IUIText();
        void draw() override;

        UIRenderable_initUIRenderableTemplate
        void _initUIText(std::string string = "parasite");

        const std::string getString();
        const IUIText &setString(std::string string);

        const float getFontSize();
        const IUIText &setFontSize(float size);

        const float getSpacing();
        const IUIText &setSpacing(float spacing);

        const Color getColour();
        const IUIText &setColour(Color colour);

        const IUIText &setFont(std::string fontPath = "parasite");

    protected:
        const Vector2 _getTextSize();
        void _updateElementSize() override;

        std::string _str;
        float _fontSize;
        float _spacing;
        Color _clr;
        Font _font;
        bool _isFontDefault;
    };
}

#include "i_ui_text.t.hxx"