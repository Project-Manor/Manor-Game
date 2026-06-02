#pragma once
#include "renderable.hxx"
#include <raylib.h>
#include <string>
#include <vector>

namespace man::things {
    class Sprite : public render::Renderable {
    public:
        Sprite();
        void draw() override;

        struct Animation {
            Animation(std::string n, std::string s, std::vector<int> p);
            std::string name;
            Texture2D spriteSheet;
            std::vector<int> switchPoints;
            int length;
            int size;
        };

        void addAnimation(Animation a);
        void playAnimation(std::string name);
        void flipSprite(bool b);
        std::string getAnimation();


    private:
        void _launch();

        Rectangle _texRec;
        int _lastAnimTick;
        bool _shouldSwitch;
        Animation _nextAnim;
        Animation _currentAnim;
        int _currentFrame;
        std::vector<Animation> _animations;
        int _flip;
    };
}
