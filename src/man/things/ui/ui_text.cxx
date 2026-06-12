#include "ui_text.hxx"
#include <raylib.h>

namespace man::things::ui {
    UIText::~UIText() {
        if (_isFontDefault) return;
        UnloadFont(_font);
    }

    auto UIText::draw() -> void {
        DrawTextEx (
            _font,
            _str.c_str(),
            {
                (float)getCalcHorizontalPosition(),
                (float)getCalcVerticalPosition()
            },
            _fontSize,
            _spacing,
            _clr
        );
    }

    auto UIText::setString(std::string string) -> const UIText& {
        _str = string;
        _updateElementSize();
        return *this;
    }

    auto UIText::setFontSize(float size) -> const UIText& {
        _fontSize = size;
        _updateElementSize();
        return *this;
    }

    auto UIText::setSpacing(float spacing) -> const UIText& {
        _spacing = spacing;
        _updateElementSize();
        return *this;
    }

    auto UIText::setColor(Color colour) -> const UIText& {
        _clr = colour;
        return *this;
    }

    auto UIText::setFont(std::string fontPath) -> const UIText& {
        if (!fontPath.compare("parasite")) {
            _font = GetFontDefault();
            _isFontDefault = true;
        }
        else {
            UnloadFont(_font);
            _font = LoadFont(fontPath.c_str());
            _isFontDefault = false;
        }

        _updateElementSize();
        return *this;
    }

    auto UIText::_updateElementSize() -> void {
        Vector2 ts = MeasureTextEx (
            _font,
            _str.c_str(),
            _fontSize,
            _spacing
        );

        _setElementSize({
            (int)ts.x,
            (int)ts.y
        });
    }
}