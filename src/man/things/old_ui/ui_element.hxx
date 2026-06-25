#pragma once
#include <raylib.h>
#include "../thing.hxx"

namespace man::things::ui {
    class UIElement : public Thing {
    public:
        UIElement();
        virtual ~UIElement();

        enum class AnchorPoint {
            Center,
            West,
            East,
            North,
            South
        };

        struct Anchor {
            AnchorPoint horizontal;
            AnchorPoint vertical;
        };

        struct Offset {
            int horizontal;
            int vertical;
        };

        struct Position {
            int horizontal;
            int vertical;
        };

        struct Size {
            int horizontal;
            int vertical;
        };

        auto getHorizontalAnchor() const -> const AnchorPoint;
        auto getVerticalAnchor() const -> const AnchorPoint;
        auto getAnchor() const -> const Anchor;

        auto getHorizontalOffset() const -> const int;
        auto getVerticalOffset() const -> const int;
        auto getOffset() const -> const Offset;

        auto setHorizontalAnchor(AnchorPoint horizontal) const -> const UIElement&;
        auto setVerticalAnchor(AnchorPoint vertical) const -> const UIElement&;
        auto setAnchor(Anchor anchor) const -> const UIElement&;

        auto setHorizontalOffset(int value) const -> const UIElement&;
        auto setVerticalOffset(int value) const -> const UIElement&;
        auto setOffset(Offset offset) const -> const UIElement&;

        auto getCalcHorizontalPosition() const -> const int;
        auto getCalcVerticalPosition() const -> const int;
        auto getCalcPosition() const -> const Position;

    protected:
        auto _setElementSize(Size size) -> void;

    private:
        mutable Anchor _anchor;
        mutable Offset _offset;
        mutable Size _size;
    };
}