#pragma once
#include "ui_element.hxx"
#include <string>
#include <raylib.h>

namespace man::things::ui {
    class Text : public Element {
    public:
        Text(std::size_t renderLayer);

        std::string getString();
        Text &setString(std::string string);

        float getFontSize();
        Text &setFontSize(float size);

        float getSpacing();
        Text &setSpacing(float spacing);

        Color getColour();
        Text &setColour(Color colour);

        Text &setFont(std::string fontPath = "parasite");

    protected:
        Vector2 _getTextSize();
        void _updateElementSize();

    private:
        std::string _str;
        float _fontSize;
        float _spacing;
        Color _clr;
        Font _font;
        bool _isFontDefault;
    };
}