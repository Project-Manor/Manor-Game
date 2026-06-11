#include "sprite.hxx"
#include "../render/renderer.hxx"
#include "../time.hxx"
#include <print>
#include <raylib.h>
#include <raymath.h>

namespace man::things {
    Sprite::Sprite() :
        _lastAnimTick(0),
        _shouldSwitch(false),
        _currentAnim({"parasite", {}, {0}}),
        _nextAnim({"parasite", {}, {0}}),
        _currentFrame(0),
        _animations({}),
        _flip(false)
    {
        _addInit(this, &Sprite::_launch);
        _model = LoadModel("res/models/quad/.obj");
        _shader = LoadShader(0, "src/man/shaders/sprite.fs");
        _model.materials[0].shader = _shader;
    }

    void Sprite::_launch() {
        if (!_animations.empty()) playAnimation(_animations[0].name);
    }

    Sprite::Animation::Animation(std::string n, std::string s, std::vector<int> p) {
        name = n;
        spriteSheet = LoadTexture(s.c_str());
        switchPoints = p;
        size = spriteSheet.height;
        length = (int)((float)spriteSheet.width / (float)size + .5f);
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
                _shouldSwitch = false;

                _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _currentAnim.spriteSheet;
            }
        }
        if (_currentFrame >= _currentAnim.length) {
            _currentFrame = 0;
        }

        int len = _currentAnim.length;
        SetShaderValue(_shader,
            GetShaderLocation(_shader, "animLength"),
            &len, SHADER_UNIFORM_INT
        );
        SetShaderValue(_shader,
            GetShaderLocation(_shader, "animFrame"),
            &_currentFrame, SHADER_UNIFORM_INT
        );
        int iFlip = _flip ? 1 : 0;
        SetShaderValue(_shader,
            GetShaderLocation(_shader, "flip"),
            &iFlip, SHADER_UNIFORM_INT
        );

        float sizeMod = _currentAnim.size / 32.0f;

        DrawModelEx(_model, _pos, {0, 1, 0}, 0, {sizeMod, sizeMod, sizeMod}, WHITE);
        // DrawBillboardRec(render::Renderer::getCamera(),
        //     _currentAnim.spriteSheet,
        //     _texRec,
        //     _pos + Vector3(0, sizeMod / 2, 0),
        //     {(float)_flip * sizeMod, 1 * sizeMod}, WHITE);
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

    void Sprite::flipSprite(bool b) {
        _flip = b;
    }

    std::string Sprite::getAnimation() { return _currentAnim.name; }

    Vector3 Sprite::getDrawPos() {
        return _pos + Vector3(0, (_currentAnim.size / 32.0f) / 2, 0);
    }
}