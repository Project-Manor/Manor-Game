#include "game.hxx"
#include "../man/things/things.hxx"
#include "modell.hxx"
#include "room.hxx"
#include "player.hxx"
#include "debug_fp_cam.hxx"
#include "npc.hxx"

void game::init() {
#ifdef DEBUG
    auto debug_cam = man::Things::create<DebugFPCamera>();
#endif
    auto player = man::Things::create<Player>();
    auto woman = man::Things::create<NPC>();
    woman->playAnimation("woman");
    woman->setPos({3, 0, 2});
    auto modell = man::Things::create<Modell>();
    modell->setPos({-2, 0, 1});
    auto room = man::Things::create<Room>();
}

void game::proc() {}

void game::term() {}