#pragma once
#include <unordered_map>
#include <raylib.h>
#include "../core.hxx"
#include "render_types.hxx"
#include "renderable.hxx"

namespace man::render {
    class Renderer {
    public:
        Renderer(const Renderer&) = delete;
        static Renderer &instance();
        static const bool isAlive();

        static const Camera3D getCamera();

        static const int getFPS();
        static void setFPS(int value);

        static const RenderIndex addRenderable(Renderable *render);
        static void removeRenderable(const RenderIndex renderIndex);

        const float getFOV();
        void setFOV(float val);

        const float getProjection();
        void setProjection(int val);

        // Position
        const float getPosX();
        void setPosX(float val);

        const float getPosY();
        void setPosY(float val);

        const float getPosZ();
        void setPosZ(float val);

        const Vector3 getPos();
        void setPos(Vector3 vec);

        const Vector3 getRot();
        void setRot(Vector3 vec);

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();

        bool _isAlive;
        Camera3D _cam;

        Vector3 camRotation;

        RenderIndex _nextRenderIndex;
        std::unordered_map <
            RenderIndex,
            Renderable*
        > _renders;
    };
}