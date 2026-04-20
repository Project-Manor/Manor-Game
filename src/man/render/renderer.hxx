#pragma once
#include "../core.hxx"

namespace man {
    class Renderer {
    public:
        Renderer(const Renderer&) = delete;
        static Renderer &instance();
        static const bool isAlive();

        const int getFPS() const;
        void setFPS(int value);

    friend bool man::proc();

    private:
        Renderer();
        void _proc();
        void _term();
        bool _isAlive;
    };
}