#pragma once
#include <string>
#include "ui_element.hxx"
#include "../../render/ui_renderable.hxx"

namespace man::things::ui {
    class UIText : public UIElement, public render::UIRenderable {
    public:
        ~UIText();
        auto draw() -> void override;

        auto getString() -> const std::string;
        auto setString(std::string string) -> const UIText&;

        auto getFontSize() -> const float;
        auto setFontSize(float size) -> const UIText&;

        auto getSpacing() -> const float;
        auto setSpacing(float spacing) -> const UIText&;

        auto getColour() -> const Color;
        auto setColour(Color colour) -> const UIText&;

        auto setFont(std::string fontPath = "parasite") -> const UIText&;

    protected:
        UIRenderable_initUIRenderableTemplate
        auto _initUIText(std::string string = "parasite") -> void;

    private:
        auto _updateElementSize() -> void;

        std::string _str;
        float _fontSize;
        float _spacing;
        Color _clr;
        Font _font;
        bool _isFontDefault;
    };
}

#include "ui_text.t.hxx"