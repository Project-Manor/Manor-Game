#pragma once
#include "ui_element.hxx"
#include <string>
#include <raylib.h>

namespace man::things::ui {
    class Sprite : public Element {
    public:
        Sprite(std::size_t renderLayer, std::string texturePath);

    private:
        std::size_t _renderLayer;
        Texture2D _tex;
        void _init();
    };
}