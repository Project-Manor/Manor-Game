#pragma once
#include "../thing.hxx"

namespace man::things::ui {
    class Element : public Thing {
    public:
        Element();

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

        Anchor getAnchor();
        Element &setHorizontalAnchor(AnchorPoint horizontal);
        Element &setVerticalAnchor(AnchorPoint vertical);
        Element &setAnchor(Anchor anchor);

        Offset getOffset();
        Element &setHorizontalOffset(int value);
        Element &setVerticalOffset(int value);
        Element &setOffset(Offset offset);

        Position getCalcPosition();

        Size getElementSize();
        void setElementSize(Size size);

    private:
        Anchor _anchor;
        Offset _offset;
        Size _size;
        Element *_parent;

        int _getCalcHPos();
        int _getCalcVPos();
    };
}