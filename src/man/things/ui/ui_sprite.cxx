#include "ui_sprite.hxx"
#include "ui_renderable.hxx"

namespace man::things::ui {
    Sprite::Sprite (
        std::size_t renderLayer,
        std::string texturePath
    ) :
        _renderLayer(renderLayer),
        _tex(LoadTexture(texturePath.c_str()))
    {
        _addSystem(SystemType::Initialization, this, &Sprite::_init);
        _addSystem(SystemType::Termination, [this]() {
            UnloadTexture(_tex);
        });
    }

    void Sprite::_init() {
        setElementSize ({
            .horizontal = _tex.width,
            .vertical = _tex.height
        });

        createChild<ui::Renderable>(_renderLayer, [this]() {
            Position pos = getCalcPosition();
            DrawTexture (
                _tex,
                pos.horizontal,
                pos.vertical,
                WHITE
            );
        });
    }
}