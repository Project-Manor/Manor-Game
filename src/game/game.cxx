#include "game.hxx"
#include <raylib.h>
#include "../man/things/things.hxx"
#include "../man/things/sprite.hxx"
#include "../man/print.hxx"

void game::init() {
    man::Things::create<man::things::Sprite>();
    auto sprite = man::Things::getTagged<man::things::Sprite>();
    if (sprite.has_value()) {
        sprite.value().get().addAnimation({
            "idle",
            LoadTexture("res/spritesheets/detective_idle.png"),
            {0}
        });
        sprite.value().get().addAnimation({
            "walk",
            LoadTexture("res/spritesheets/detective_walk.png"),
            {2, 5}
        });
        sprite.value().get().playAnimation("idle");
    }
}

void game::proc() {
    if (IsKeyPressed(KEY_SPACE)) {
        auto sprite = man::Things::getTagged<man::things::Sprite>();
        if (sprite.has_value()) {
            if (sprite.value().get().getAnimation() == "idle")
                sprite.value().get().playAnimation("walk");
            else
                sprite.value().get().playAnimation("idle");
        }
    }
}

void game::term() {}