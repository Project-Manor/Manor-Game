#pragma once
#include "../render/renderable.hxx"
#include "spatial.hxx"
#include <raylib.h>
#include <string>
#include <vector>
#include <array>


namespace man::things {
    class Sprite : public Spatial, public man::render::Renderable {
    public:
        TAG(Sprite);

        Sprite();
        void launch() override;
        void process() override;
        void finish() override;
        void draw() override;

        struct Animation {
            Animation(std::string n, Texture2D s, std::vector<int> p);
            std::string name;
            Texture2D spriteSheet;
            std::vector<int> switchPoints;
            int length;
            int size;
        };

        void addAnimation(Animation a);
        void playAnimation(std::string name);
        std::string getAnimation();


    private:
        Rectangle _texRec;
        int _lastAnimTick;
        bool _shouldSwitch;
        Animation _nextAnim;
        Animation _currentAnim;
        int _currentFrame;
        std::vector<Animation> _animations;
    };
}
