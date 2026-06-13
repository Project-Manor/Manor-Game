#include "renderer.hxx"
#include "raylib.h"
#include "raymath.h"
#include "../things/renderable.hxx"
#include <unordered_map>
#include <vector>
#include <algorithm>

#ifdef DEBUG
#include "../things/things.hxx"
#include "../../game/collision/collision.hxx"
#include "../../game/player.hxx"
#endif

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
        _worldRenderTex({0}),
        _uiRenderTex({0}),
        _nextRenderIndex(0),
        _worldRenders({}),
        _uiRenders({}),
        _camRotation({0}),
        _camZ({0}),
        _camX({0})
    {
        #ifndef DEBUG
            SetTraceLogLevel(LOG_NONE);
        #endif

        InitWindow (
            DEFAULT_HORIZONTAL_RESOLUTION,
            DEFAULT_VERTICAL_RESOLUTION,
            "Manor Game"
        );

        setFPS(60);

        _worldRenderTex = LoadRenderTexture (
            DEFAULT_HORIZONTAL_RESOLUTION * WORLD_RENDER_RESOLUTION_MULTIPLIER,
            DEFAULT_VERTICAL_RESOLUTION * WORLD_RENDER_RESOLUTION_MULTIPLIER
        );

        _uiRenderTex = LoadRenderTexture (
            DEFAULT_HORIZONTAL_RESOLUTION,
            DEFAULT_VERTICAL_RESOLUTION
        );
    }

    void Renderer::_proc() {
        if (WindowShouldClose()) {
            _term();
            return;
        }

        if (IsWindowResized())
            _updateRenderTexRes();

        if (IsKeyPressed(KEY_ONE)) {
            setResolution({854, 480});
        }
        else if (IsKeyPressed(KEY_TWO)) {
            setResolution({1280, 720});
        }
        else if (IsKeyPressed(KEY_THREE)) {
            setResolution({1920, 1080});
        }

        BeginTextureMode(_worldRenderTex); {
            BeginMode3D(_cam); {
                ClearBackground(SKYBLUE);
                for (auto &[i , r] : _worldRenders) {
                    r->draw();
                }
                #ifdef DEBUG
                    world::Collision::drawLines();
                    auto player = man::Things::getTagged<Player>("player");
                    player->debugDraw();
                #endif
                EndMode3D();
            }

            EndTextureMode();
        }

        BeginTextureMode(_uiRenderTex); {
            ClearBackground(BLANK);

            for (std::unordered_set<UIRenderable*> &set : _uiRenders)
                for (UIRenderable *render : set)
                    render->draw();

            EndTextureMode();
        }

        auto drawTexPro = [](RenderTexture2D rt) {
            DrawTexturePro (
                rt.texture,
                {
                    0.0f,
                    0.0f,
                    (float)rt.texture.width,
                    -(float)rt.texture.height
                },
                {
                    0.0f,
                    0.0f,
                    (float)getResolution().horizontal,
                    (float)getResolution().vertical
                },
                {0.0f, 0.0f},
                0.0f,
                WHITE
            );
        };

        BeginDrawing(); {
            ClearBackground(BLANK);
            drawTexPro(_worldRenderTex);
            drawTexPro(_uiRenderTex);
            EndDrawing();
        }
    }

    void Renderer::_term() {
        UnloadRenderTexture(_worldRenderTex);
        UnloadRenderTexture(_uiRenderTex);
        CloseWindow();
        instance()._isAlive = false;
    }

    void Renderer::_updateRenderTexRes() {
        auto r = getResolution();

        UnloadRenderTexture(_worldRenderTex);
        _worldRenderTex = LoadRenderTexture (
            r.horizontal * WORLD_RENDER_RESOLUTION_MULTIPLIER,
            r.vertical * WORLD_RENDER_RESOLUTION_MULTIPLIER
        );

        UnloadRenderTexture(_uiRenderTex);
        _uiRenderTex = LoadRenderTexture (
            r.horizontal,
            r.vertical
        );
    }

    // void Renderer::_drawWorldRenders() {
    //     // Sort renderables by distance from camera.
    //     std::unordered_map<float, std::vector<Renderable*>> unsorted;
    //     unsorted.reserve(_worldRenders.size());
    //     std::vector<Renderable*> sorted;
    //     sorted.reserve(_worldRenders.size());
    //     std::vector<float> keys;
    //     keys.reserve(_worldRenders.size());

    //     for (auto &[i , r] : _worldRenders) {
    //         float dist = Vector3Distance(r->getPos(), getPos());
    //         if (!unsorted.contains(dist))
    //             keys.emplace_back(dist);
    //         unsorted[dist].emplace_back(r);
    //     }
    //     for (auto &[i, r] : unsorted) {
    //         for (auto &j : r) {
    //             Vector3 pos = j->getPos();
    //         }
    //     }
    //     std::sort(keys.begin(), keys.end());
    //     for (auto &i : keys) {
    //         for (auto &j : unsorted[i]) {
    //             sorted.emplace_back(j);
    //             Vector3 pos = j->getPos();
    //         }
    //     }
    //     for (int i = sorted.size() - 1; i >= 0; i--)
    //         sorted[i]->draw();
    // }
}