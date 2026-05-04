#include "sprite.hxx"
#include "../render/renderer.hxx"
#include "../time.hxx"
#include <raylib.h>
#include <raymath.h>

namespace man::things {
    Sprite::Sprite() :
        _texRec({}),
        _lastAnimTick(0),
        _shouldSwitch(false),
        _currentAnim({"parasite", {}, {0}}),
        _nextAnim({"parasite", {}, {0}}),
        _currentFrame(0),
        _animations({})
    {}

    Sprite::Animation::Animation(std::string n, Texture2D s, std::vector<int> p) {
        name = n;
        spriteSheet = s;
        switchPoints = p;
        size = spriteSheet.height;
        length = (int)((float)spriteSheet.width / (float)size + .5f);
    }

    void Sprite::launch() {

    }

    void Sprite::process() {

    }

    void Sprite::finish() {

    }

    void Sprite::draw() {
        for (int i : _currentAnim.switchPoints) {
            if (_currentFrame == i && _currentAnim.name != _nextAnim.name) {
                _shouldSwitch = true;
                break;
            }
        }
        if (Time::animTick() > _lastAnimTick) {
            _currentFrame++;
            _lastAnimTick = Time::animTick();
            if (_shouldSwitch) {
                _currentAnim = _nextAnim;
                _currentFrame = 0;
                _texRec = {0, 0, (float)_currentAnim.size, (float)_currentAnim.size};
                _shouldSwitch = false;
            }
        }
        if (_currentFrame >= _currentAnim.length) {
            _currentFrame = 0;
        }
        _texRec.x = _currentFrame * _currentAnim.size;
        DrawBillboardRec(render::Renderer::getCamera(), _currentAnim.spriteSheet, _texRec, _pos, {1, 1}, WHITE);
    }

    void Sprite::addAnimation(Sprite::Animation a) {
        _animations.emplace_back(a);
    }

    void Sprite::playAnimation(std::string name) {
        for (Animation &a : _animations) {
            if (a.name == name) {
                _nextAnim = a;
                break;
            }
        }
    }

    std::string Sprite::getAnimation() { return _currentAnim.name; }
}