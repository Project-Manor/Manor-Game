#include "spatial.hxx"
#include "raylib.h"

namespace man::things {
    Spatial::Spatial() :
        _pos({0})
    {}

    Vector3 Spatial::getPos() { return _pos; }
    void Spatial::setPos(Vector3 p) {
        _pos = p;
    }
}