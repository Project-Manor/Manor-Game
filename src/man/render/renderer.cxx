#include "renderer.hxx"
#include "raylib.h"
#include "renderable.hxx"

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
            .position = {.0f, .0f, .0f},
            .target = {.0f, .0f, .0f},
            .up = {.0f, .0f, .0f},
            .fovy = .0f,
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
    const float Renderer::Camera::getFOV()
    { return instance()._cam.fovy; }

    void Renderer::Camera::setFOV(float val)
    { instance()._cam.fovy = val; }

    // Camera Projection
    const float Renderer::Camera::getProjection()
    { return instance()._cam.projection; }

    void Renderer::Camera::setProjection(int val)
    { instance()._cam.projection = val; }

    // Camera Position
    const float Renderer::Camera::getPosX()
    { return instance()._cam.position.x; }

    void Renderer::Camera::setPosX(float val)
    { instance()._cam.position.x = val; }

    const float Renderer::Camera::getPosY()
    { return instance()._cam.position.y; }

    void Renderer::Camera::setPosY(float val)
    { instance()._cam.position.y = val; }

    const float Renderer::Camera::getPosZ()
    { return instance()._cam.position.z; }

    void Renderer::Camera::setPosZ(float val)
    { instance()._cam.position.z = val; }

    const Vector3 Renderer::Camera::getPos() { return {
        getPosX(),
        getPosY(),
        getPosZ()
    };}

    void Renderer::Camera::setPos(Vector3 vec) {
        setPosX(vec.x);
        setPosY(vec.y);
        setPosZ(vec.z);
    }

    // Camera Target
    const float Renderer::Camera::getTargetX()
    { return instance()._cam.target.x; }

    void Renderer::Camera::setTargetX(float val)
    { instance()._cam.target.x = val; }

    const float Renderer::Camera::getTargetY()
    { return instance()._cam.target.y; }

    void Renderer::Camera::setTargetY(float val)
    { instance()._cam.target.y = val; }

    const float Renderer::Camera::getTargetZ()
    { return instance()._cam.target.z; }

    void Renderer::Camera::setTargetZ(float val)
    { instance()._cam.target.z = val; }

    const Vector3 Renderer::Camera::getTarget() { return {
        getTargetX(),
        getTargetY(),
        getTargetZ()
    };}

    void Renderer::Camera::setTarget(Vector3 vec) {
        setTargetX(vec.x);
        setTargetY(vec.y);
        setTargetZ(vec.z);
    }

    // Camera Up
    const float Renderer::Camera::getUpX()
    { return instance()._cam.up.x; }

    void Renderer::Camera::setUpX(float val)
    { instance()._cam.up.x = val; }

    const float Renderer::Camera::getUpY()
    { return instance()._cam.up.y; }

    void Renderer::Camera::setUpY(float val)
    { instance()._cam.up.y = val; }

    const float Renderer::Camera::getUpZ()
    { return instance()._cam.up.z; }

    void Renderer::Camera::setUpZ(float val)
    { instance()._cam.up.z = val; }

    const Vector3 Renderer::Camera::getUp() { return {
        getUpX(),
        getUpY(),
        getUpZ()
    };}

    void Renderer::Camera::setUp(Vector3 vec) {
        setUpX(vec.x);
        setUpY(vec.y);
        setUpZ(vec.z);
    }
}