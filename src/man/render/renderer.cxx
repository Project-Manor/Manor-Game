#include "renderer.hxx"
#include "raylib.h"
#include "raymath.h"
#include "../things/renderable.hxx"
#include "cmath"
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace man::render {
    Renderer &Renderer::instance() {
        static Renderer inst;
        return inst;
    }

    const bool Renderer::isAlive()
    { return instance()._isAlive; }

    const Camera3D &Renderer::getCamera()
    { return instance()._cam; }

    const Renderer::Resolution Renderer::getResolution() {
        return {
            GetScreenWidth(),
            GetScreenHeight()
        };
    }

    void Renderer::setResolution(Renderer::Resolution res) {
        SetWindowSize(res.horizontal, res.vertical);
    }

    const int Renderer::getFPS()
    { return GetFPS(); }

    void Renderer::setFPS(int value)
    { SetTargetFPS(value); }

    Renderer::Renderer() :
        _isAlive(true),
        _cam({
            .position = {0.0f, .5f, 1.0f},
            .target = {.0f, .0f, .0f},
            .up = {.0f, 1.0f, .0f},
            .fovy = 60.0f,
            .projection = CAMERA_PERSPECTIVE
        }),
        _uiRenders({}),
        _nextRenderIndex(0),
        _renders({}),
        _camRotation({0}),
        _camZ({0}),
        _camX({0})
    {
        #ifndef DEBUG
            SetTraceLogLevel(LOG_NONE);
        #endif

        InitWindow(800, 450, "Manor Game");
        SetWindowState(FLAG_WINDOW_RESIZABLE);
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

        // Sort renderables by distance from camera.
        std::unordered_map<float, std::vector<Renderable*>> unsorted;
        unsorted.reserve(_renders.size());
        std::vector<Renderable*> sorted;
        sorted.reserve(_renders.size());
        std::vector<float> keys;
        keys.reserve(_renders.size());

        for (auto &[i , r] : _renders) {
            float dist = Vector3Distance(r->getPos(), getPos());
            if (!unsorted.contains(dist))
                keys.emplace_back(dist);
            unsorted[dist].emplace_back(r);
        }
        for (auto &[i, r] : unsorted) {
            for (auto &j : r) {
                Vector3 pos = j->getPos();
            }
        }
        std::sort(keys.begin(), keys.end());
        for (auto &i : keys) {
            for (auto &j : unsorted[i]) {
                sorted.emplace_back(j);
                Vector3 pos = j->getPos();
            }
        }
        for (int i = sorted.size() - 1; i >= 0; i--)
            sorted[i]->draw();

        EndMode3D();

        for (std::unordered_set<UIRenderable*> &set : _uiRenders)
            for (UIRenderable *render : set)
                render->draw();

        EndDrawing();
    }

    void Renderer::addUIRenderable(const int layer, UIRenderable *render)
    { instance()._uiRenders[layer].emplace(render); }

    void Renderer::removeUIRenderable(const int layer, UIRenderable *render)
    { instance()._uiRenders[layer].erase(render); }

    const long long Renderer::addRenderable(Renderable *render) {
        Renderer &inst = instance();
        inst._renders.emplace(inst._nextRenderIndex, render);
        return inst._nextRenderIndex++;
    }

    void Renderer::removeRenderable(const long long renderIndex)
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
        return instance()._camRotation;
    }

    void Renderer::setRot(Vector3 v) {
        Vector3 vec = v + Vector3(0, 180);
        #define DEG_2_RAD (float)0.017453292519943295769236907684886f

        float l = std::cos(vec.x * DEG_2_RAD);
        float y = std::sin(vec.x * DEG_2_RAD);
        float x = std::sin(vec.y * DEG_2_RAD) * l;
        float z = std::cos(vec.y * DEG_2_RAD) * l;

        float xx = std::sin((vec.y - 90) * DEG_2_RAD) * l;
        float zx = std::cos((vec.y - 90) * DEG_2_RAD) * l;

        instance()._camZ = Vector3Normalize({x, y, z});
        instance()._camX = Vector3Normalize({xx, y, zx});

        instance()._camRotation = v;
        instance()._cam.target = Vector3Add(getPos(), {x, y, z});
    }

    const Vector3 Renderer::getCamZ() {
        return instance()._camZ;
    }

    const Vector3 Renderer::getCamX() {
        return instance()._camX;
    }
}