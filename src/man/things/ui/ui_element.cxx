#include "ui_element.hxx"
#include "../../render/renderer.hxx"

namespace man::things::ui {
    UIElement::UIElement() :
        _hAnchor(Anchor::Horizontal::Center),
        _vAnchor(Anchor::Vertical::Center),
        _hOffset(0.0f),
        _vOffset(0.0f)
    {}

    UIElement::~UIElement() = default;

    auto UIElement::getHorizontalAnchor() const -> const Anchor::Horizontal
    { return _hAnchor; }

    auto UIElement::getVerticalAnchor() const -> const Anchor::Vertical
    { return _vAnchor; }

    auto UIElement::getAnchor() const -> const Anchor {
        return {
            .horizontal = getHorizontalAnchor(),
            .vertical = getVerticalAnchor()
        };
    }

    auto UIElement::getHorizontalOffset() const -> const float
    { return _hOffset; }

    auto UIElement::getVerticalOffset() const -> const float
    { return _vOffset; }

    auto UIElement::getOffset() const -> const Offset {
        return {
            .horizontal = getHorizontalOffset(),
            .vertical = getVerticalOffset()
        };
    }

    auto UIElement::setHorizontalAnchor(Anchor::Horizontal horizontal) const -> const UIElement& {
        _hAnchor = horizontal;
        return *this;
    }

    auto UIElement::setVerticalAnchor(Anchor::Vertical vertical) const -> const UIElement& {
        _vAnchor = vertical;
        return *this;
    }

    auto UIElement::setAnchor(Anchor anchor) const -> const UIElement& {
        setHorizontalAnchor(anchor.horizontal);
        return setVerticalAnchor(anchor.vertical);
    }

    auto UIElement::setHorizontalOffset(float value) const -> const UIElement& {
        _hOffset = value;
        return *this;
    }

    auto UIElement::setVerticalOffset(float value) const -> const UIElement& {
        _vOffset = value;
        return *this;
    }

    auto UIElement::setOffset(Offset offset) const -> const UIElement& {
        setHorizontalOffset(offset.horizontal);
        return setVerticalOffset(offset.vertical);
    }

    auto UIElement::getCalcHorizontalPosition(const Texture &tex) const -> const int {
        const int hRes = man::render::Renderer::getUIRenderTextureSize().first;
        const float texMod = (float)tex.width / 2;

        switch (_hAnchor) {
            case Anchor::Horizontal::West:
                return _hOffset - texMod;

            case Anchor::Horizontal::East:
                return hRes - _hOffset - texMod;

            case Anchor::Horizontal::Center:
                return ((float)hRes / 2) + _hOffset - texMod;
        }
    }

    auto UIElement::getCalcVerticalPosition(const Texture &tex) const -> const int {
        const int vRes = man::render::Renderer::getUIRenderTextureSize().second;
        const float texMod = (float)tex.height / 2;

        switch (_vAnchor) {
            case Anchor::Vertical::North:
                return _vOffset - texMod;

            case Anchor::Vertical::South:
                return vRes - _vOffset - texMod;

            case Anchor::Vertical::Center:
                return ((float)vRes / 2) + _vOffset - texMod;
        }
    }

    auto UIElement::getCalcPosition(const Texture &tex) const -> const Position {
        return {
            getCalcHorizontalPosition(tex),
            getCalcVerticalPosition(tex)
        };
    }
}