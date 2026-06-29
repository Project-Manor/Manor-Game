#include "player.hxx"
#include "raylib.h"
#include "raymath.h"
#include "collision/collision.hxx"
#include "cmath"
#include <cstdlib>
#include <man>
#include <renderable.hxx>

Player::Player() :
    // Movement
    _speed(11),
    _deceleration(4),
    _acceleration(4),
    _currentSpeed(0),
    _lastMoveVec({}),

    // Collision
    _collisionRadius(0.2)
{
    _addSystem(SystemType::Initialization, this, &Player::_init);

    if constexpr (man::kDebug)
        _addSystem(SystemType::Initialization, this, &Player::_spawnDebugRenderable);

    _addProc(this, &Player::_movement);
}

void Player::_init() {
    using namespace man::things;

    Sprite::addAnimation({
        "idle",
        "res/spritesheets/detective_idle.png",
        {0}
    });

    Sprite::addAnimation({
        "walk",
        "res/spritesheets/detective_walk.png",
        {2, 5}
    });
}

Player::collision::collision(Vector2 p, Vector2 n, float d, bool b) {
    pos = p;
    normal = n;
    dist = d;
    isEdge = b;
}

void Player::_movement() {
    // Get input direction
    Vector3 inputVec = {};
    if (IsKeyDown(KEY_W)) inputVec.z--;
    if (IsKeyDown(KEY_S)) inputVec.z++;
    if (IsKeyDown(KEY_A)) inputVec.x--;
    if (IsKeyDown(KEY_D)) inputVec.x++;
    Vector3 moveVec = Vector3Normalize(inputVec);

    if (Vector3Length(moveVec) == 0)
        moveVec = _lastMoveVec;
    else
        _lastMoveVec = moveVec;

    if (moveVec.x < 0) man::things::Sprite::flipSprite(true);
    if (moveVec.x > 0) man::things::Sprite::flipSprite(false);
    if (Vector3Length(inputVec) > 0) {
        man::things::Sprite::playAnimation("walk");
        _currentSpeed = Clamp(_currentSpeed + _acceleration * _speed * man::Time::deltaTime(), 0, _speed);
    }
    else {
        man::things::Sprite::playAnimation("idle");
        _currentSpeed = Clamp(_currentSpeed - _deceleration * _speed * man::Time::deltaTime(), 0, _speed);
    }

    Vector3 velocity = moveVec * _currentSpeed / 16 * man::Time::deltaTime();

    _pos = _moveAndCollide(_pos, velocity);
}

Vector3 Player::_moveAndCollide(Vector3 pos, Vector3 vel) {
    Vector3 nextPos = pos + vel;
    std::vector<collision> collisions = _getCollisions(nextPos);
    if (!collisions.empty()) {
        float dist = collisions[0].dist;
        Vector2 normal = collisions[0].normal;
        for (int i = 1; i < collisions.size(); i++) {
            if (!collisions[i].isEdge) {
                if (collisions[i].dist > dist) {
                    normal = Vector2Lerp(normal, collisions[i].normal, 0.5);
                    dist = std::max(dist, collisions[i].dist);
                }
            }
        }

        Vector2 pushBack = normal * dist;
        if (Vector3Length(vel + (Vector3){pushBack.x, 0, pushBack.y}) < man::Time::deltaTime() / 3.0) {
            return pos;
        }

        return nextPos + (Vector3){pushBack.x, 0, pushBack.y};
    }
    return nextPos;
}

// Vector3 Player::_collideAndSlide(Vector3 pos, Vector3 vel, int depth) {
//     if (depth >= _maxBounces)
//         return {0, 0, 0};

//     std::vector<collision> collisions = _getCollisions(pos + vel);
//     if (!collisions.empty()) {
//         collision hit = collisions[0];
//         Vector3 dir = Vector3Normalize(vel);
//         Vector3 norm = {hit.normal.x, 0, hit.normal.y};
//         Vector3 snap2Surf = vel + norm * hit.dist;

//         return _collideAndSlide(pos + snap2Surf, {0, 0, 0}, depth + 1);
//     }

//     return vel;
// }

// Vector3 Player::_solveCollision(Vector3 pos, int depth) {
//     if (depth >= _maxBounces)
//         return {0, 0, 0};

//     std::vector<collision> collisions = _getCollisions(pos);
//     if (!collisions.empty()) {
//         collision hit = collisions[0];
//         Vector3 pushback = (Vector3){hit.normal.x, 0, hit.normal.y} * hit.dist;

//         return _solveCollision(pos + pushback, depth + 1);
//     }

//     return pos;
// }

std::vector<Player::collision> Player::_getCollisions(Vector3 pos) {
    std::vector<collision> collisions = {};

    for (const world::Collision::CollisionLine &l : world::Collision::getLines()) {
        // Check if object is near the line. Otherwise skip line.
        float minX = std::min(l.point1.x, l.point2.x);
        float maxX = std::max(l.point1.x, l.point2.x);
        float minY = std::min(l.point1.y, l.point2.y);
        float maxY = std::max(l.point1.y, l.point2.y);
        if (!(
            pos.x > minX - _collisionRadius &&
            pos.x < maxX + _collisionRadius &&
            pos.z > minY - _collisionRadius &&
            pos.z < maxY + _collisionRadius
        )) {
            continue;
        }

        Vector2 p = {pos.x, pos.z};

        // Calculate center of line overlap.
        Vector2 dir = Vector2Normalize(l.point1 - l.point2);
        Vector2 vec2Obj = p - l.point1;
        float d = Vector2DotProduct(dir, vec2Obj);

        Vector2 center = l.point1 + dir * d;

        Vector2 normal = Vector2Normalize(Vector2{pos.x, pos.z} - center);

        // Calculate if object is paralell with line or at an edge.
        auto area = [](Vector2 va, Vector2 vb, Vector2 vc) {
            return abs(
                (vb.x * va.y - va.x * vb.y) +
                (vc.x * vb.y - vb.x * vc.y) +
                (va.x * vc.y - vc.x * va.y)
            ) / 2.0f;
        };

        float recArea = Vector2Distance(l.point1, l.point2) * _collisionRadius;

        Vector2 p1 = l.point1;
        Vector2 p2 = l.point1 + normal * _collisionRadius;
        Vector2 p3 = l.point2;
        Vector2 p4 = l.point2 + normal * _collisionRadius;

        Vector2 collisionCenter = center;
        Vector2 collisionNormal = normal;
        float collisionDistance = 0;
        bool isEdge = false;

        if (
            area(p1, p, p4) +
            area(p4, p, p3) +
            area(p3, p, p2) +
            area(p, p2, p1) > recArea
        ){
            // Edge - Edge case!
            // Check if object is near the edge.
            if (!(
                Vector2Distance(p, p1) <= _collisionRadius ||
                Vector2Distance(p, p3) <= _collisionRadius))
            { continue; }

            isEdge = true;

            float p1Dist = Vector2Distance(p, l.point1);
            float p2Dist = Vector2Distance(p, l.point2);

            if (p1Dist <= p2Dist) {
                collisionNormal = Vector2Normalize(p - p1);
                collisionCenter = p1;
                collisionDistance = Vector2Distance(p, collisionCenter);
            }
            else {
                collisionNormal = Vector2Normalize(p - p3);
                collisionCenter = p3;
                collisionDistance = Vector2Distance(p, collisionCenter);
            }
        }
        else {
            // Object is parallell.
            float a = l.point1.y - l.point2.y;
            float b = l.point2.x - l.point1.x;
            float c = (l.point1.x * l.point2.y) - (l.point1.y * l.point2.x);
            collisionDistance = (abs(a * pos.x + b * pos.z + c)) / sqrt(a * a + b * b);

            if (collisionDistance > _collisionRadius) {
                continue;
            }
        }
        collisions.emplace_back((collision){collisionCenter, collisionNormal, _collisionRadius - collisionDistance, isEdge});
    }

    for (int i = 0; i < collisions.size(); i++) {
        if (!collisions[i].isEdge) {
            iter_swap(collisions.begin() + i, collisions.begin());
        }
    }

    return collisions;
}

void Player::_spawnDebugRenderable() {
    createChild<Renderable>([this]() {
        std::vector<collision> collisions = _getCollisions(_pos);
        if (!collisions.empty()) {
            Vector2 pos = collisions[0].pos;
            Vector2 normal = collisions[0].normal;
            DrawLine3D(
                {pos.x, 0, pos.y},
                (Vector3){pos.x, 0, pos.y} + (Vector3){normal.x, 0, normal.y} * collisions[0].dist,
                BLUE
            );
            DrawCircle3D(
                {pos.x, 0, pos.y},
                0.05f,
                {1, 0, 0},
                90,
                PURPLE
            );
        }
        Color colClr = collisions.empty() ? WHITE : RED;
        DrawCircle3D(
            {_pos.x, 0, _pos.z},
            _collisionRadius,
            {1, 0, 0},
            90,
            colClr
        );
    });
}