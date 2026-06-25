#pragma once
#include <raylib.h>

namespace man::iui {
    class IUIElement {
    public:
        IUIElement();
        virtual ~IUIElement();

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

        const AnchorPoint getHorizontalAnchor() const;
        const AnchorPoint getVerticalAnchor() const;
        const Anchor getAnchor() const;

        const int getHorizontalOffset() const;
        const int getVerticalOffset() const;
        const Offset getOffset() const;

        const IUIElement &setHorizontalAnchor(AnchorPoint horizontal) const;
        const IUIElement &setVerticalAnchor(AnchorPoint vertical) const;
        const IUIElement &setAnchor(Anchor anchor) const;

        const IUIElement &setHorizontalOffset(int value) const;
        const IUIElement &setVerticalOffset(int value) const;
        const IUIElement &setOffset(Offset offset) const;

        const int getCalcHorizontalPosition() const;
        const int getCalcVerticalPosition() const;
        const Position getCalcPosition() const;

    protected:
        void _setElementSize(Size size);
        virtual void _updateElementSize() = 0;

    private:
        mutable Anchor _anchor;
        mutable Offset _offset;
        mutable Size _size;
    };
}