#include "room.hxx"

Room::Room() {
    _initModel(
        "res/models/room.obj",
        "res/models/white.png",
        "src/shaders/fog.fs",
        "src/shaders/fog.vs"
    );
}