#include "i_ui_element.hxx"
#include "../../../render/renderer.hxx"
#include "../../../print.hxx"
#include "../../../str_colour.hxx"

namespace man::iui {
    IUIElement::IUIElement() :
        _anchor ({
            AnchorPoint::Center,
            AnchorPoint::Center
        }),
        _offset({0, 0}),
        _size({0, 0})
    {}

    IUIElement::~IUIElement() = default;

    const IUIElement::AnchorPoint IUIElement::getHorizontalAnchor() const
    { return _anchor.horizontal; }

    const IUIElement::AnchorPoint IUIElement::getVerticalAnchor() const
    { return _anchor.vertical; }

    const IUIElement::Anchor IUIElement::getAnchor() const
    { return _anchor; }

    const int IUIElement::getHorizontalOffset() const
    { return _offset.horizontal; }

    const int IUIElement::getVerticalOffset() const
    { return _offset.vertical; }

    const IUIElement::Offset IUIElement::getOffset() const
    { return _offset; }

    const IUIElement &IUIElement::setHorizontalAnchor(AnchorPoint horizontal) const {
        _anchor.horizontal = horizontal;
        return *this;
    }

    const IUIElement &IUIElement::setVerticalAnchor(AnchorPoint vertical) const {
        _anchor.vertical = vertical;
        return *this;
    }

    const IUIElement &IUIElement::setAnchor(Anchor anchor) const {
        _anchor = anchor;
        return *this;
    }

    const IUIElement &IUIElement::setHorizontalOffset(int value) const {
        _offset.horizontal = value;
        return *this;
    }

    const IUIElement &IUIElement::setVerticalOffset(int value) const {
        _offset.vertical = value;
        return *this;
    }

    const IUIElement &IUIElement::setOffset(Offset offset) const {
        _offset = offset;
        return *this;
    }

    const int IUIElement::getCalcHorizontalPosition() const {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _offset.horizontal;

        switch (_anchor.horizontal) {
            case AnchorPoint::North:
                printspace();
                println (
                    man::strYellow("| IUIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::North"),
                    ", it's not horizontal dumb*ss!"
                );
                printspace();
                goto centerCase;

            case AnchorPoint::South:
                printspace();
                println (
                    man::strYellow("| IUIElement Warning:"),
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

    const int IUIElement::getCalcVerticalPosition() const {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (res.second / (float)1080) * _offset.vertical;

        switch (_anchor.vertical) {
            case AnchorPoint::West:
                printspace();
                println (
                    man::strYellow("| IUIElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::West"),
                    ", it's not vertical dumb*ss!"
                );
                printspace();
                goto centerCase;

            case AnchorPoint::East:
                printspace();
                println (
                    man::strYellow("| IUIElement Warning:"),
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

    const IUIElement::Position IUIElement::getCalcPosition() const {
        return {
            getCalcHorizontalPosition(),
            getCalcVerticalPosition()
        };
    }

    void IUIElement::_setElementSize(Size size)
    { _size = size; }
}