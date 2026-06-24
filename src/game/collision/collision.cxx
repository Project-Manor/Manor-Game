#include "collision.hxx"
#include <core.hxx>
#include <things>

namespace world {
    Collision::Collision() {
        if constexpr (!man::kDebug) return;

        man::things::createThing<man::render::Renderable>([]() {
            if (!instance()._debug) return;

            for (CollisionLine l : instance()._lines) {
                DrawLine3D(
                    {l.point1.x, 0, l.point1.y},
                    {l.point2.x, 0, l.point2.y},
                    LIME
                );
            }
        });
    }

    Collision &world::Collision::instance() {
        static Collision inst;
        return inst;
    }

    Collision::CollisionLine::CollisionLine(Vector2 p1, Vector2 p2) {
        point1 = p1;
        point2 = p2;
    }

    std::vector<Collision::CollisionLine> Collision::getLines() {
        return instance()._lines;
    }

    void Collision::addLine(Vector2 p1, Vector2 p2) {
        CollisionLine l = {p1, p2};
        instance()._lines.emplace_back(l);
    }

    #ifdef DEBUG
    void Collision::debug(bool b) {
        instance()._debug = b;
    }
    #endif
}