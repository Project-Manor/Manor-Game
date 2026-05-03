#include "man/core.hxx"
#include "game/game.hxx"

int main(int argc, char **argv) {
    man::init();
    game::init();

    while (man::proc())
        game::proc();

    game::term();
    man::term();

    return 0;
}