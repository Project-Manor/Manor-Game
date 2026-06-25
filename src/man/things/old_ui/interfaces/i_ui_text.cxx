#include "i_ui_text.hxx"
#include <raylib.h>

namespace man::iui {
    IUIText::~IUIText() {
        if (_isFontDefault) return;
        UnloadFont(_font);
    }

    void IUIText::draw() {
        DrawTextEx (
            _font,
            _str.c_str(),
            {
                .x = (float)getCalcHorizontalPosition(),
                .y = (float)getCalcVerticalPosition()
            },
            _fontSize,
            _spacing,
            _clr
        );
    }

    const std::string IUIText::getString()
    { return _str; }

    const IUIText &IUIText::setString(std::string string) {
        _str = string;
        _updateElementSize();
        return *this;
    }

    const float IUIText::getFontSize()
    { return _fontSize; }

    const IUIText &IUIText::setFontSize(float size) {
        _fontSize = size;
        _updateElementSize();
        return *this;
    }

    const float IUIText::getSpacing()
    { return _spacing; }

    const IUIText &IUIText::setSpacing(float spacing) {
        _spacing = spacing;
        _updateElementSize();
        return *this;
    }

    const Color IUIText::getColour()
    { return _clr; }

    const IUIText &IUIText::setColour(Color colour) {
        _clr = colour;
        return *this;
    }

    const IUIText &IUIText::setFont(std::string fontPath) {
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

    const Vector2 IUIText::_getTextSize() {
        return MeasureTextEx (
            _font,
            _str.c_str(),
            _fontSize,
            _spacing
        );
    }

    void IUIText::_updateElementSize() {
        const Vector2 ts = _getTextSize();
        _setElementSize({
            (int)ts.x,
            (int)ts.y
        });
    }
}