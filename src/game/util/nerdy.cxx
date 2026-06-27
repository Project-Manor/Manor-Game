#include "nerdy.hxx"
#include <render/renderer.hxx>
#include <time.hxx>
#include <format>
#include <raylib.h>
#include <rlgl.h>

#include <print.hxx>

namespace game::util {
    Nerdy::Nerdy() :
        _renderLayer(std::size_t{69}),
        _fontPath("res/fonts/PressStart2P-vaV7.ttf"),
        _textSize(12),
        _port ({
            .port = createChild<man::things::ui::Element>(),
            .opengl = {nullptr},
            .fps = {nullptr},
            .time = {nullptr}
        }),

        _star ({
            .star = createChild<man::things::ui::Element>()
        })
    {
        _addSystem(SystemType::Initialization, this,
            &Nerdy::_populatePort,
            &Nerdy::_populateStar
        );

        _addSystem(SystemType::Process, this,
            &Nerdy::_sailPort,
            &Nerdy::_sailStar,
            &Nerdy::_adjustGunwale
        );
    }

    void Nerdy::_populatePort() {
        using namespace man::things::ui;

        _port.port->setHorizontalAnchor (
            Element::AnchorPoint::West
        );

        _port.opengl = _port.port->createChild<Text>(_renderLayer);
        _port.opengl->setAnchor ({
            .horizontal = Element::AnchorPoint::West,
            .vertical = Element::AnchorPoint::North
        });
        _port.opengl->
            setFont(_fontPath).
            setFontSize(_textSize).
            setString(std::format("OpenGL Version: {}", rlGetVersion()))
        ;

        _port.fps = _port.port->createChild<Text>(_renderLayer);
        _port.fps->
            setAnchor ({
                .horizontal = Element::AnchorPoint::West,
                .vertical = Element::AnchorPoint::North
            }).
            setVerticalOffset (
                _port.opengl->getElementSize().vertical
            )
        ;
        _port.fps->
            setFont(_fontPath).
            setFontSize(_textSize)
        ;

        _port.time = _port.port->createChild<Text>(_renderLayer);
        _port.time->setAnchor ({
            .horizontal = Element::AnchorPoint::West,
            .vertical = Element::AnchorPoint::South
        });
        _port.time->
            setFont(_fontPath).
            setFontSize(_textSize)
        ;
    }

    void Nerdy::_populateStar() {
        using namespace man::things::ui;

        _star.star->setHorizontalAnchor (
            Element::AnchorPoint::East
        );
    }

    void Nerdy::_sailPort() {
        _port.fps->setString(std::format (
            "FPS: {}",
            man::render::Renderer::getFPS()
        ));

        _port.time->setString(std::format (
            "Time: {}\nTick: {}\nDelta Time: {}\nAnimation Tick: {}",
            man::Time::time(),
            man::Time::tick(),
            man::Time::deltaTime(),
            man::Time::animTick()
        ));
    }

    void Nerdy::_sailStar() {}

    void Nerdy::_adjustGunwale() {
        auto r = man::render::Renderer::getUIRenderTextureSize();
        man::things::ui::Element::Size s = {
            .horizontal = r.first / 2,
            .vertical = r.second
        };

        _port.port->setElementSize(s);
        _star.star->setElementSize(s);
    }
}