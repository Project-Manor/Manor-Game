#include "renderer.hxx"
#include "raylib.h"
#include "raymath.h"
#include "../things/renderable.hxx"
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace man::render {
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
        _drawRenders();
        EndMode3D();

        for (std::unordered_set<UIRenderable*> &set : _uiRenders)
            for (UIRenderable *render : set)
                render->draw();

        EndDrawing();
    }

    void Renderer::_term() {
        CloseWindow();
        instance()._isAlive = false;
    }

    void Renderer::_drawRenders() {
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
    }
}