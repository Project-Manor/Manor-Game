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
    auto player = man::Things::create<Player>();
    auto npc = man::Things::create<NPC>();
}

void game::proc() {}

void game::term() {}