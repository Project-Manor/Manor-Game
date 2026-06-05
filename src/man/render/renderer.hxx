#pragma once
#include <unordered_map>
#include <raylib.h>
#include "../core.hxx"
#include "../things/renderable.hxx"

namespace man::render {
    class Renderer {
    public:
        Renderer(const Renderer&) = delete;
        static Renderer &instance();
        static const bool isAlive();

        static const Camera3D &getCamera();

        static const int getFPS();
        static void setFPS(int value);

        static const long long addRenderable(Renderable *render);
        static void removeRenderable(const long long renderIndex);

        const float getFOV();
        void setFOV(float val);

        const float getProjection();
        void setProjection(int val);

        // Position
        static const float getPosX();
        void setPosX(float val);

        static const float getPosY();
        void setPosY(float val);

        static const float getPosZ();
        void setPosZ(float val);

        static const Vector3 getPos();
        void setPos(Vector3 vec);

        static const Vector3 getRot();
        void setRot(Vector3 vec);

        static const Vector3 getCamZ();
        static const Vector3 getCamX();

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();

        bool _isAlive;
        Camera3D _cam;

        Vector3 _camRotation;
        Vector3 _camZ;
        Vector3 _camX;

        long long _nextRenderIndex;
        std::unordered_map <
            long long,
            Renderable*
        > _renders;
    };
}