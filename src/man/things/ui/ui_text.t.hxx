#pragma once
#include "ui_text.hxx"
#include <raylib.h>

UIRenderable_initUIRenderableTemplate
void man::things::ui::UIText::_initUIText (
    std::string str,
    float fontSize,
    float spacing,
    Color clr,
    std::string fontPath
) {
    _initUIRenderable<RenderLayer>();

    _str = str;
    _fontSize = fontSize;
    _spacing = spacing;
    _clr = clr;

    if (!fontPath.compare("parasite")) {
        _font = GetFontDefault();
        _isFontDefault = true;
    }
    else {
        _font = LoadFont(fontPath.c_str());
        _isFontDefault = false;
    }

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