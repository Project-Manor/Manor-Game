#include "npc.hxx"

NPC::NPC() {
    man::things::Sprite::addAnimation({
        "woman",
        "res/sprites/woman.png",
        {0}
    });
    man::things::Sprite::addAnimation({
        "magnor",
        "res/sprites/magnor_arachnid.png",
        {0}
    });
}