#pragma once
#include "ui_text.hxx"

UIRenderable_initUIRenderableTemplate
void man::things::ui::UIText::_initUIText (
    std::string str,
    Font font,
    float fontSize,
    float spacing,
    Color clr
) {
    _initUIRenderable<RenderLayer>();
    _str = str;
    _font = font;
    _fontSize = fontSize;
    _spacing = spacing;
    _clr = clr;

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