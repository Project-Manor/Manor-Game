#include "ui_text.hxx"
#include <raylib.h>

namespace man::things::ui {
    UIText::~UIText() = default;

    void UIText::draw() {
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
}