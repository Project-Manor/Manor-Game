#include "ui_element.hxx"
#include "../../render/renderer.hxx"
#include "../../print.hxx"
#include "../../str_colour.hxx"

namespace man::things::ui {
    UIElement::UIElement() :
        _anchor ({
            AnchorPoint::Center,
            AnchorPoint::Center
        }),
        _offset({0, 0}),
        _size({0, 0})
    {}

    UIElement::~UIElement() = default;

    auto UIElement::getHorizontalAnchor() const -> const AnchorPoint
    { return _anchor.horizontal; }

    auto UIElement::getVerticalAnchor() const -> const AnchorPoint
    { return _anchor.vertical; }

    auto UIElement::getAnchor() const -> const Anchor
    { return _anchor; }

    auto UIElement::getHorizontalOffset() const -> const int
    { return _offset.horizontal; }

    auto UIElement::getVerticalOffset() const -> const int
    { return _offset.vertical; }

    auto UIElement::getOffset() const -> const Offset
    { return _offset; }

    auto UIElement::setHorizontalAnchor(AnchorPoint horizontal) const -> const UIElement& {
        _anchor.horizontal = horizontal;
        return *this;
    }

    auto UIElement::setVerticalAnchor(AnchorPoint vertical) const -> const UIElement& {
        _anchor.vertical = vertical;
        return *this;
    }

    auto UIElement::setAnchor(Anchor anchor) const -> const UIElement& {
        _anchor = anchor;
        return *this;
    }

    auto UIElement::setHorizontalOffset(int value) const -> const UIElement& {
        _offset.horizontal = value;
        return *this;
    }

    auto UIElement::setVerticalOffset(int value) const -> const UIElement& {
        _offset.vertical = value;
        return *this;
    }

    auto UIElement::setOffset(Offset offset) const -> const UIElement& {
        _offset = offset;
        return *this;
    }

    auto UIElement::getCalcHorizontalPosition() const -> const int {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _offset.horizontal;

        switch (_anchor.horizontal) {
            case AnchorPoint::North:
                printspace();
                println (
                    man::strYellow("| UIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::North"),
                    ", it's not horizontal dumb*ss!"
                );
                printspace();
                goto centerCase;

            case AnchorPoint::South:
                printspace();
                println (
                    man::strYellow("| UIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::South"),
                    ", it's not horizontal dumb*ss!"
                );
                printspace();
                [[fallthrough]];

            case AnchorPoint::Center:
                label: centerCase:
                return ((float)res.first / 2) + offset - ((float)_size.horizontal / 2);

            case AnchorPoint::West:
                return offset;

            case AnchorPoint::East:
                return res.first + offset - (float)_size.horizontal;
        }
    }

    auto UIElement::getCalcVerticalPosition() const -> const int {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _offset.vertical;

        switch (_anchor.vertical) {
            case AnchorPoint::West:
                printspace();
                println (
                    man::strYellow("| UIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::West"),
                    ", it's not vertical dumb*ss!"
                );
                printspace();
                goto centerCase;

            case AnchorPoint::East:
                printspace();
                println (
                    man::strYellow("| UIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::East"),
                    ", it's not vertical dumb*ss!"
                );
                printspace();
                [[fallthrough]];

            case AnchorPoint::Center:
                label: centerCase:
                return ((float)res.second / 2) + offset - ((float)_size.vertical / 2);

            case AnchorPoint::North:
                return offset;

            case AnchorPoint::South:
                return res.second + offset - (float)_size.vertical;
        }
    }

    auto UIElement::getCalcPosition() const -> const Position {
        return {
            getCalcHorizontalPosition(),
            getCalcVerticalPosition()
        };
    }

    auto UIElement::_setElementSize(Size size) -> void
    { _size = size; }
}