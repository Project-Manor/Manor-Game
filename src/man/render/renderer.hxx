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

        static const int getFPS();
        static void setFPS(int value);

        static const RenderIndex addRenderable(Renderable *render);
        static void removeRenderable(const RenderIndex renderIndex);

        static struct Camera {
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

            // Target
            const float getTargetX();
            void setTargetX(float val);

            const float getTargetY();
            void setTargetY(float val);

            const float getTargetZ();
            void setTargetZ(float val);

            const Vector3 getTarget();
            void setTarget(Vector3 vec);

            // Up
            const float getUpX();
            void setUpX(float val);

            const float getUpY();
            void setUpY(float val);

            const float getUpZ();
            void setUpZ(float val);

            const Vector3 getUp();
            void setUp(Vector3 vec);
        } camera;

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();

        bool _isAlive;
        Camera3D _cam;

        RenderIndex _nextRenderIndex;
        std::unordered_map <
            RenderIndex,
            Renderable*
        > _renders;
    };
}