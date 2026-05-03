#pragma once
#include "thing.hxx"
#include <raylib.h>

namespace man::things {
    class Spatial : public Thing {
    public:
        Spatial();
        virtual ~Spatial();

    protected:
        Vector3 _pos;
    };
}