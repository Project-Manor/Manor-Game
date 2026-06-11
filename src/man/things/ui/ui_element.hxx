#pragma once
#include <raylib.h>
#include "../thing.hxx"

namespace man::things::ui {
    class UIElement : public Thing {
    public:
        UIElement();
        virtual ~UIElement();

        struct Anchor {
            enum class Horizontal {
                Center,
                West,
                East
            } horizontal;

            enum class Vertical {
                Center,
                North,
                South
            } vertical;
        };

        struct Offset {
            int horizontal;
            int vertical;
        };

        struct Position {
            int horizontal;
            int vertical;
        };

        auto getHorizontalAnchor() const -> const Anchor::Horizontal;
        auto getVerticalAnchor() const -> const Anchor::Vertical;
        auto getAnchor() const -> const Anchor;

        auto getHorizontalOffset() const -> const int;
        auto getVerticalOffset() const -> const int;
        auto getOffset() const -> const Offset;

        auto setHorizontalAnchor(Anchor::Horizontal horizontal) const -> const UIElement&;
        auto setVerticalAnchor(Anchor::Vertical vertical) const -> const UIElement&;
        auto setAnchor(Anchor anchor) const -> const UIElement&;

        auto setHorizontalOffset(int value) const -> const UIElement&;
        auto setVerticalOffset(int value) const -> const UIElement&;
        auto setOffset(Offset offset) const -> const UIElement&;

        auto getCalcHorizontalPosition(const Texture &tex) const -> const int;
        auto getCalcVerticalPosition(const Texture &tex) const -> const int;
        auto getCalcPosition(const Texture &tex) const -> const Position;

    private:
        mutable Anchor::Horizontal _hAnchor;
        mutable Anchor::Vertical _vAnchor;
        mutable int _hOffset;
        mutable int _vOffset;
    };
}