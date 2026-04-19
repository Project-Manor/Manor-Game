#pragma once

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

namespace man {
    namespace ent {
        struct Transform {
            Transform();
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
        };
    }
}