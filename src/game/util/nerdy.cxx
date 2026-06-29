#include "nerdy.hxx"
#include <render/renderer.hxx>
#include <time.hxx>
#include <format>
#include <raylib.h>
#include <rlgl.h>
#include <input>

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
            .star = createChild<man::things::ui::Element>(),
            .entriesLabel = {nullptr},
            .createdEntries = {nullptr},
            .aliveEntries = {nullptr},
            .deadEntries = {nullptr}
        })
    {
        _addSystem(SystemType::Initialization, this,
            &Nerdy::_populatePort,
            &Nerdy::_populateStar,
            &Nerdy::_undock
        );

        _addSystem(SystemType::Process, this,
            &Nerdy::_sailPort,
            &Nerdy::_sailStar,
            &Nerdy::_adjustGunwale,
            [this]() {
                if (!input::pressed(input::ui::DockNerdy)) return;
                _port.port->isActive() ? _undock() : _dock();
            }
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

        Element::Anchor childAnch = {
            .horizontal = Element::AnchorPoint::East,
            .vertical = Element::AnchorPoint::North
        };

        _star.entriesLabel = _star.star->createChild<Text>(_renderLayer);
        _star.entriesLabel->setAnchor(childAnch);
        _star.entriesLabel->
            setFont(_fontPath).
            setFontSize(_textSize).
            setString("- Registry Entry Stats -")
        ;

        _star.createdEntries = _star.star->createChild<Text>(_renderLayer);
        _star.createdEntries->setAnchor(childAnch).setVerticalOffset (
            _star.entriesLabel->getElementSize().vertical
        );
        _star.createdEntries->
            setFont(_fontPath).
            setFontSize(_textSize)
        ;

        _star.aliveEntries = _star.star->createChild<Text>(_renderLayer);
        _star.aliveEntries->setAnchor(childAnch).setVerticalOffset (
            _star.createdEntries->getOffset().vertical +
            _star.createdEntries->getElementSize().vertical
        );
        _star.aliveEntries->
            setFont(_fontPath).
            setFontSize(_textSize)
        ;

        _star.deadEntries = _star.star->createChild<Text>(_renderLayer);
        _star.deadEntries->setAnchor(childAnch).setVerticalOffset (
            _star.aliveEntries->getOffset().vertical +
            _star.aliveEntries->getElementSize().vertical
        );
        _star.deadEntries->
            setFont(_fontPath).
            setFontSize(_textSize)
        ;
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

    void Nerdy::_sailStar() {
        _star.createdEntries->setString(std::format (
            "{} :Created",
            man::registry::tracking::getTotalCreatedEntries()
        ));

        _star.aliveEntries->setString(std::format (
            "{} :ALive",
            man::registry::tracking::getTotalAliveEntries()
        ));

        _star.deadEntries->setString(std::format (
            "{} :Dead",
            man::registry::tracking::getTotalDeadEntries()
        ));
    }

    void Nerdy::_adjustGunwale() {
        auto r = man::render::Renderer::getUIRenderTextureSize();
        man::things::ui::Element::Size s = {
            .horizontal = r.first / 2,
            .vertical = r.second
        };

        _port.port->setElementSize(s);
        _star.star->setElementSize(s);
    }

    void Nerdy::_dock() {
        _port.port->activate();
        _star.star->activate();
    }

    void Nerdy::_undock() {
        _port.port->deactivate();
        _star.star->deactivate();
    }
}