#include "game.hxx"
#include "../man/things/things.hxx"
#include "room.hxx"
#include "player.hxx"
#include "debug_fp_cam.hxx"
#include "npc.hxx"

void game::init() {
#ifdef DEBUG
    auto debug_cam = man::Things::create<DebugFPCamera>();
#endif
    auto magnor = man::Things::create<NPC>();
    auto player = man::Things::create<Player>();
    auto woman = man::Things::create<NPC>();
    woman->playAnimation("woman");
    woman->setPos({3, 0, 2});
    magnor->playAnimation("magnor");
    magnor->setPos({-2, 0, -3});
}

void game::proc() {}

void game::term() {}