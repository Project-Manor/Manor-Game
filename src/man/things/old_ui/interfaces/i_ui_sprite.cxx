#include "i_ui_sprite.hxx"
#include <raylib.h>

namespace man::iui {
    IUISprite::~IUISprite() {
        UnloadTexture(_tex);
    }

    void IUISprite::draw() {
        DrawTexture (
            _tex,
            getCalcHorizontalPosition(),
            getCalcVerticalPosition(),
            WHITE
        );
    }

    const Vector2 IUISprite::_getTextureSize() {
        return {
            .x = (float)_tex.width,
            .y = (float)_tex.height
        };
    }

    void IUISprite::_updateElementSize() {
        const Vector2 ts = _getTextureSize();
        _setElementSize ({
            .horizontal = (int)ts.x,
            .vertical = (int)ts.y
        });
    }
}