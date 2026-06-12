#pragma once
#include "ui_text.hxx"
#include <raylib.h>

UIRenderable_initUIRenderableTemplate
void man::things::ui::UIText::_initUIText(std::string string) {
    _initUIRenderable<RenderLayer>();
    _str = string;

    _fontSize = 67;
    _spacing = 4;
    _clr = WHITE;

    setFont();
}