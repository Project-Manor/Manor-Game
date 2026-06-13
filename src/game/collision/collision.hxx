#pragma once

#include "raylib.h"
#include "../../man/things/renderable.hxx"
#include <vector>

namespace world {
    class Collision {
    public:
        Collision(const Collision&) = delete;
        static Collision &instance();

        struct CollisionLine {
            CollisionLine(Vector2 p1, Vector2 p2);

            Vector2 point1;
            Vector2 point2;
        };

        static std::vector<CollisionLine> getLines();

        static void addLine(Vector2 p1, Vector2 p2);

        #ifdef DEBUG
        static void debug(bool b);
        static void drawLines();
        #endif

    private :
        Collision() {};

        std::vector<CollisionLine> _lines;

        bool _debug;
    };
}