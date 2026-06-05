#include "ui_element.hxx"
#include <algorithm>

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

    auto UIElement::setHorizontalOffset(float percentile) const -> const UIElement& {
        _hOffset = std::clamp(percentile, 0.0f, 100.0f);
        return *this;
    }

    auto UIElement::setVerticalOffset(float percentile) const -> const UIElement& {
        _vOffset = std::clamp(percentile, 0.0f, 100.0f);
        return *this;
    }

    auto UIElement::setOffset(Offset offset) const -> const UIElement& {
        setHorizontalOffset(offset.horizontal);
        return setVerticalOffset(offset.vertical);
    }
}