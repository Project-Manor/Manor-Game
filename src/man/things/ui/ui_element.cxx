#include "ui_element.hxx"
#include "../../render/renderer.hxx"
#include "../../print.hxx"
#include "../../str_colour.hxx"

#ifdef DEBUG
#include <core.hxx>
#include "ui_renderable.hxx"
#include <raylib.h>
#endif

namespace man::things::ui {
    Element::Element() :
        _anchor ({
            AnchorPoint::Center,
            AnchorPoint::Center
        }),
        _offset({0, 0}),
        _size({0, 0}),
        _parent(nullptr)
    {
        if (auto p = getParentAs<Element>(); p)
            _parent = p.get();

        if constexpr (man::kDebug)
            createChild<ui::Renderable>(std::size_t{42}, [this]() {
                Position pos = getCalcPosition();
                DrawRectangleLinesEx (
                    {
                        .x = static_cast<float>(pos.horizontal),
                        .y = static_cast<float>(pos.vertical),
                        .width = static_cast<float>(_size.horizontal),
                        .height = static_cast<float>(_size.vertical)
                    },
                    .67,
                    MAGENTA
                );
            });
    }

    Element::Anchor Element::getAnchor() { return _anchor; }

    Element &Element::setHorizontalAnchor(AnchorPoint horizontal) {
        _anchor.horizontal = horizontal;
        return *this;
    }

    Element &Element::setVerticalAnchor(AnchorPoint vertical) {
        _anchor.vertical = vertical;
        return *this;
    }

    Element &Element::setAnchor(Anchor anchor) {
        _anchor = anchor;
        return *this;
    }

    Element::Offset Element::getOffset() { return _offset; }

    Element &Element::setHorizontalOffset(int value) {
        _offset.horizontal = value;
        return *this;
    }

    Element &Element::setVerticalOffset(int value) {
        _offset.vertical = value;
        return *this;
    }

    Element &Element::setOffset(Offset offset) {
        _offset = offset;
        return *this;
    }

    Element::Position Element::getCalcPosition() {
        return {
            .horizontal = _getCalcHPos(),
            .vertical = _getCalcVPos()
        };
    }

    Element::Size Element::getElementSize() { return _size; }
    void Element::setElementSize(Size size) { _size = size; }

    int Element::_getCalcHPos() {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (_parent)
            ? _offset.horizontal
            : (res.second / (float)1080) * _offset.horizontal
        ;

        switch (_anchor.horizontal) {
            case AnchorPoint::North:
                man::printspace();
                man::println (
                    man::strYellow("| Element Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::North"),
                    ", it's not horizontal dumb*ss!"
                );
                man::printspace();
                goto centerCase;

            case AnchorPoint::South:
                man::printspace();
                man::println (
                    man::strYellow("| Element Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::South"),
                    ", it's not horizontal dumb*ss!"
                );
                man::printspace();
                [[fallthrough]];

            case AnchorPoint::Center:
                centerCase:

                if (_parent) return (
                    _parent->_getCalcHPos() +
                    static_cast<float>(_parent->_size.horizontal) / 2 +
                    offset -
                    static_cast<float>(_size.horizontal) / 2
                );

                else return (
                    static_cast<float>(res.first) / 2 +
                    offset -
                    static_cast<float>(_size.horizontal) / 2
                );

            case AnchorPoint::West:
                if (_parent) return (
                    _parent->_getCalcHPos() +
                    offset
                );

                else return offset;

            case AnchorPoint::East:
                if (_parent) return (
                    _parent->_getCalcHPos() +
                    _parent->_size.horizontal +
                    offset -
                    static_cast<float>(_size.horizontal)
                );

                else return (
                    res.first +
                    offset -
                    static_cast<float>(_size.horizontal)
                );
        }
    }

    int Element::_getCalcVPos() {
        const auto res = man::render::Renderer::getUIRenderTextureSize();
        const float offset = (_parent)
            ? _offset.vertical
            : (res.second / (float)1080) * _offset.vertical
        ;

        switch (_anchor.vertical) {
            case AnchorPoint::West:
                man::printspace();
                man::println (
                    man::strYellow("| Element Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::West"),
                    ", it's not vertical dumb*ss!"
                );
                man::printspace();
                goto centerCase;

            case AnchorPoint::East:
                printspace();
                println (
                    man::strYellow("| IElement Warning:"),
                    " Ignoring ",
                    man::strCyan("AnchorPoint::East"),
                    ", it's not vertical dumb*ss!"
                );
                printspace();
                [[fallthrough]];

            case AnchorPoint::Center:
                centerCase:
                if (_parent) return (
                    _parent->_getCalcVPos() +
                    static_cast<float>(_parent->_size.vertical) / 2 +
                    offset -
                    static_cast<float>(_size.vertical) / 2
                );

                else return (
                    static_cast<float>(res.second) / 2 +
                    offset -
                    static_cast<float>(_size.vertical) / 2
                );

            case AnchorPoint::North:
                if (_parent) return (
                    _parent->_getCalcVPos() +
                    offset
                );

                else return offset;

            case AnchorPoint::South:
                if (_parent) return (
                    _parent->_getCalcVPos() +
                    _parent->_size.vertical +
                    offset -
                    static_cast<float>(_size.vertical)
                );

                else return (
                    res.second +
                    offset -
                    static_cast<float>(_size.vertical)
                );
        }
    }
}