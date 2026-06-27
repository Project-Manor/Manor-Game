#include "ui_text.hxx"
#include "ui_renderable.hxx"

namespace man::things::ui {
    Text::Text(std::size_t renderLayer) :
        _str("parasite"),
        _fontSize(67),
        _spacing(4),
        _clr(WHITE),
        _font(GetFontDefault()),
        _isFontDefault(true)
    {
        _updateElementSize();

        createChild<ui::Renderable>(renderLayer, [this]() {
            Position pos = getCalcPosition();
            DrawTextEx (
                _font,
                _str.c_str(),
                {
                    .x = static_cast<float>(pos.horizontal),
                    .y = static_cast<float>(pos.vertical)
                },
                _fontSize,
                _spacing,
                _clr
            );
        });

        _addSystem(SystemType::Termination, [this]() {
            if (_isFontDefault) return;
            UnloadFont(_font);
        });
    }

    std::string Text::getString() { return _str; }
    Text &Text::setString(std::string string) {
        _str = string;
        _updateElementSize();
        return *this;
    }

    float Text::getFontSize() { return _fontSize; }
    Text &Text::setFontSize(float size) {
        _fontSize = size;
        _updateElementSize();
        return *this;
    }

    float Text::getSpacing() { return _spacing; }
    Text &Text::setSpacing(float spacing) {
        _spacing = spacing;
        _updateElementSize();
        return *this;
    }

    Color Text::getColour() { return _clr; }
    Text &Text::setColour(Color colour) {
        _clr = colour;
        return *this;
    }

    Text &Text::setFont(std::string fontPath) {
        if (!_isFontDefault) UnloadFont(_font);

        _font = LoadFont(fontPath.c_str());
        _isFontDefault = false;

        _updateElementSize();
        return *this;
    }

    Vector2 Text::_getTextSize() {
        return MeasureTextEx (
            _font,
            _str.c_str(),
            _fontSize,
            _spacing
        );
    }

    void Text::_updateElementSize() {
        const Vector2 ts = _getTextSize();
        setElementSize({
            (int)ts.x,
            (int)ts.y
        });
    }
}