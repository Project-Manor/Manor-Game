#pragma once
#include "core.hxx"
#include <string>

namespace man {
    class Time {
    public:
        Time(const Time&) = delete;
        static Time &instance();

        static const long long &tick();
        static const float &deltaTime();
        static const int &animTick();

        static const std::string stringedData();

    friend void man::init();
    friend bool man::proc();

    private:
        Time();
        void _proc();

        const double _startTime;
        long long _tick;
        double _time;
        double _prevTime;
        float _deltaTime;
        int _animTick;
        const int _animFPS;
    };
}