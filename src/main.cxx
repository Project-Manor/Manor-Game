#include "man_engine/core.hxx"

int main(int argc, char **argv) {
    man::init();

    while (man::proc());

    man::term();
    return 0;
}