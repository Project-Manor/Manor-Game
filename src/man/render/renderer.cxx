#include "renderer.hxx"
#include "raylib.h"
#include "raymath.h"
#include "renderable.hxx"
#include "cmath"
#include <print>

namespace man::render {
    Renderer &Renderer::instance() {
        static Renderer inst;
        return inst;
    }

    const bool Renderer::isAlive()
    { return instance()._isAlive; }

    const int Renderer::getFPS()
    { return GetFPS(); }

    void Renderer::setFPS(int value)
    { SetTargetFPS(value); }

    Renderer::Renderer() :
        _isAlive(true),
        _cam({
            .position = {10.0f, 10.0f, 10.0f},
            .target = {.0f, .0f, .0f},
            .up = {.0f, 1.0f, .0f},
            .fovy = 60.0f,
            .projection = CAMERA_PERSPECTIVE
        }),
        _nextRenderIndex(0),
        _renders({})
    {
        #ifndef DEBUG
            SetTraceLogLevel(LOG_NONE);
        #endif

        InitWindow(800, 450, "Manor Game");
        setFPS(60);
    }

    void Renderer::_proc() {
        if (WindowShouldClose()) {
            _term();
            return;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(_cam);

        for (auto &[index, render] : _renders)
            render->draw();

        EndMode3D();
        EndDrawing();
    }

    const RenderIndex Renderer::addRenderable(Renderable *render) {
        Renderer &inst = instance();
        inst._renders.emplace(inst._nextRenderIndex, render);
        return inst._nextRenderIndex++;
    }

    void Renderer::removeRenderable(const RenderIndex renderIndex)
    { instance()._renders.erase(renderIndex); }

    void Renderer::_term() {
        CloseWindow();
        instance()._isAlive = false;
    }

    // Camera FOV
    const float Renderer::getFOV()
    { return instance()._cam.fovy; }

    void Renderer::setFOV(float val)
    { instance()._cam.fovy = val; }

    // Camera Projection
    const float Renderer::getProjection()
    { return instance()._cam.projection; }

    void Renderer::setProjection(int val)
    { instance()._cam.projection = val; }

    // Camera Position
    const float Renderer::getPosX()
    { return instance()._cam.position.x; }

    void Renderer::setPosX(float val)
    { instance()._cam.position.x = val; }

    const float Renderer::getPosY()
    { return instance()._cam.position.y; }

    void Renderer::setPosY(float val)
    { instance()._cam.position.y = val; }

    const float Renderer::getPosZ()
    { return instance()._cam.position.z; }

    void Renderer::setPosZ(float val)
    { instance()._cam.position.z = val; }

    const Vector3 Renderer::getPos() { return {
        getPosX(),
        getPosY(),
        getPosZ()
    };}

    void Renderer::setPos(Vector3 vec) {
        setPosX(vec.x);
        setPosY(vec.y);
        setPosZ(vec.z);
    }

    // Camera Rotation
    const Vector3 Renderer::getRot() {
        return instance().camRotation;
    }

    void Renderer::setRot(Vector3 vec) {
        const float DEG_2_RAD = 0.017453292519943295769236907684886f;

        float l = std::cos(vec.x * DEG_2_RAD);
        float y = std::sin(vec.x * DEG_2_RAD) * l;
        float x = std::sin(vec.y * DEG_2_RAD) * l;
        float z = std::cos(vec.y * DEG_2_RAD) * l;

        instance().camRotation = vec;
        instance()._cam.target = Vector3Add(getPos(), {x, y, z});
    }
}