#pragma once
#include <string>
#include "ui_element.hxx"
#include "../../render/ui_renderable.hxx"

namespace man::things::ui {
    class UIText : public UIElement, public render::UIRenderable {
    public:
        ~UIText();
        auto draw() -> void override;

        auto setString(std::string string) -> const UIText&;
        auto setFontSize(float size) -> const UIText&;
        auto setSpacing(float spacing) -> const UIText&;
        auto setColor(Color colour) -> const UIText&;
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