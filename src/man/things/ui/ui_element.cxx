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

    auto UIElement::getHorizontalOffset() const -> const int
    { return _hOffset; }

    auto UIElement::getVerticalOffset() const -> const int
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

    auto UIElement::setHorizontalOffset(int value) const -> const UIElement& {
        _hOffset = value;
        return *this;
    }

    auto UIElement::setVerticalOffset(int value) const -> const UIElement& {
        _vOffset = value;
        return *this;
    }

    auto UIElement::setOffset(Offset offset) const -> const UIElement& {
        setHorizontalOffset(offset.horizontal);
        return setVerticalOffset(offset.vertical);
    }

    auto UIElement::getCalcHorizontalPosition(const Texture &tex) const -> const int {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _hOffset;

        switch (_hAnchor) {
            case Anchor::Horizontal::Center:
                return ((float)res.first / 2) + offset - ((float)tex.width / 2);

            case Anchor::Horizontal::West:
                return offset;

            case Anchor::Horizontal::East:
                return res.first + offset - (float)tex.width;
        }
    }

    auto UIElement::getCalcVerticalPosition(const Texture &tex) const -> const int {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _vOffset;

        switch (_vAnchor) {
            case Anchor::Vertical::Center:
                return ((float)res.second / 2) + offset - ((float)tex.height / 2);

            case Anchor::Vertical::North:
                return offset;

            case Anchor::Vertical::South:
                return res.second + offset - (float)tex.height;
        }
    }

    auto UIElement::getCalcPosition(const Texture &tex) const -> const Position {
        return {
            getCalcHorizontalPosition(tex),
            getCalcVerticalPosition(tex)
        };
    }
}