#include "engine/core.hxx"

int main(int argc, char **argv) {
    engine::init();

    while (engine::proc());

    engine::term();
    return 0;
}