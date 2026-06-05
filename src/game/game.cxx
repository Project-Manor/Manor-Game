#include "game.hxx"
#include "../man/things/things.hxx"
#include "debug_fp_cam.hxx"

void game::init() {
#ifdef DEBUG
    auto debug_cam = man::Things::create<DebugFPCamera>();
#endif
}

void game::proc() {}

void game::term() {}