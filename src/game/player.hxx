#pragma once
#include "../man/things/sprite.hxx"
#include <raylib.h>
#include <vector>
#include <optional>

class Player : public man::things::Sprite {
public:
    Player();
    #ifdef DEBUG
    void debugDraw();
    #endif

private:
    void _movement();
    Vector3 _moveAndCollide(Vector3, Vector3);
    Vector3 _collideAndSlide(Vector3, Vector3, int);
    Vector3 _solveCollision(Vector3, int);


    // Movement
    const int _speed;
    const int _acceleration;
    const int _deceleration;
    float _currentSpeed;
    Vector3 _lastMoveVec;

    // Collision
    struct collision {
        collision(Vector2, Vector2, float, bool);
        Vector2 pos;
        Vector2 normal;
        float dist;
        bool isEdge;
    };

    std::vector<collision> _getCollisions(Vector3);

    const int _maxBounces = 5;
    const float _collisionRadius;
    Vector3 _lastPos;

    // Debug
    #ifdef DEBUG
    bool _debugIsColliding;
    #endif
};