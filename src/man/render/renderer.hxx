#pragma once
#include <array>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <raylib.h>
#include "../core.hxx"
#include "ui_renderable.hxx"
#include "../things/renderable.hxx"

#define DEFAULT_HORIZONTAL_RESOLUTION 800
#define DEFAULT_VERTICAL_RESOLUTION 450

#define WORLD_RENDER_RESOLUTION_MULTIPLIER 1.0f

namespace man::render {
    class Renderer {
    public:
        struct Resolution { int horizontal; int vertical; };

        Renderer(const Renderer&) = delete;
        static Renderer &instance();
        static const bool isAlive();

        static const Camera3D &getCamera();

        static const Resolution getResolution();
        static void setResolution(Resolution res);

        static std::pair<int, int> getWorldRenderTextureSize();
        static std::pair<int, int> getUIRenderTextureSize();

        static const int getFPS();
        static void setFPS(int value);

        static void addUIRenderable(const int layer, UIRenderable *render);
        static void removeUIRenderable(const int layer, UIRenderable *render);

        static const long long addRenderable(Renderable *render);
        static void removeRenderable(const long long renderIndex);

        static const float getFOV();
        static void setFOV(float val);

        static const float getProjection();
        static void setProjection(int val);

        // Position
        static const float getPosX();
        static void setPosX(float val);

        static const float getPosY();
        static void setPosY(float val);

        static const float getPosZ();
        static void setPosZ(float val);

        static const Vector3 getPos();
        static void setPos(Vector3 vec);

        static const Vector3 getRot();
        static void setRot(Vector3 vec);

        static const Vector3 getCamZ();
        static const Vector3 getCamX();

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();

        void _updateRenderTexRes();
        void _drawWorldRenders();

        bool _isAlive;
        Camera3D _cam;

        Vector3 _camRotation;
        Vector3 _camZ;
        Vector3 _camX;

        RenderTexture2D _worldRenderTex;
        RenderTexture2D _uiRenderTex;

        long long _nextRenderIndex;
        std::unordered_map <
            long long,
            Renderable*
        > _worldRenders;

        std::array <
            std::unordered_set<UIRenderable*>,
            16
        > _uiRenders;
    };
}