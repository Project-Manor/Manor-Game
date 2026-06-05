#pragma once
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
            float horizontal;
            float vertical;
        };

        auto getHorizontalAnchor() const -> const Anchor::Horizontal;
        auto getVerticalAnchor() const -> const Anchor::Vertical;
        auto getAnchor() const -> const Anchor;

        auto getHorizontalOffset() const -> const float;
        auto getVerticalOffset() const -> const float;
        auto getOffset() const -> const Offset;

        auto setHorizontalAnchor(Anchor::Horizontal horizontal) const -> const UIElement&;
        auto setVerticalAnchor(Anchor::Vertical vertical) const -> const UIElement&;
        auto setAnchor(Anchor anchor) const -> const UIElement&;

        auto setHorizontalOffset(float percentile) const -> const UIElement&;
        auto setVerticalOffset(float percentile) const -> const UIElement&;
        auto setOffset(Offset offset) const -> const UIElement&;

    private:
        mutable Anchor::Horizontal _hAnchor;
        mutable Anchor::Vertical _vAnchor;
        mutable float _hOffset;
        mutable float _vOffset;
    };
}