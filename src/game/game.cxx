#include "game.hxx"
#include "../man/things/things.hxx"
#include "../man/things/sprite.hxx"
#include "player.hxx"

void game::init() {
    auto player = man::Things::create<Player>();
}

void game::proc() {}

void game::term() {}