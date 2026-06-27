#pragma once
#include <things>
#include <registry>
#include <ui>

namespace game::util {
    class Nerdy : public man::things::Thing {
    public:
        Nerdy();

    private:
        const std::size_t _renderLayer;
        const std::string _fontPath;
        const float _textSize;

        struct PortSide {
            man::registry::Reference<man::things::ui::Element> port;
            man::registry::Reference<man::things::ui::Text> opengl;
            man::registry::Reference<man::things::ui::Text> fps;
            man::registry::Reference<man::things::ui::Text> time;
        } _port;

        struct Starboard {
            man::registry::Reference<man::things::ui::Element> star;
        } _star;

        void _populatePort(), _populateStar();
        void _sailPort(), _sailStar();
        void _adjustGunwale();
    };
}