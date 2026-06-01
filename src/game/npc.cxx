#include "npc.hxx"

NPC::NPC() {
    man::things::Sprite::addAnimation({
        "idle",
        "res/sprites/woman.png",
        {0}
    });

    _pos = {3, 0, -2};
}