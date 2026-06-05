#pragma once
#include "thing.hxx"
#include <raylib.h>

namespace man::things {
    class Spatial : public Thing {
    public:
        Spatial();
        Vector3 getPos();
        void setPos(Vector3);

    protected:
        Vector3 _pos;
    };
}