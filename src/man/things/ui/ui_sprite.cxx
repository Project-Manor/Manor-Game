#include "ui_sprite.hxx"
#include <raylib.h>

namespace man::things::ui {
    UISprite::~UISprite() {
        UnloadTexture(_tex);
    }

    void UISprite::draw() {
        DrawTexture (
            _tex,
            getCalcHorizontalPosition(),
            getCalcVerticalPosition(),
            WHITE
        );
    }
}