#pragma once
#include "core.hxx"
#include <chrono>

namespace man {
    class Time {
    public:
        Time(const Time&) = delete;
        static Time &instance();

        static const long long &tick();
        static const float &deltaTime();
        static const long long &frameTick();

    friend void man::init();
    friend bool man::proc();

    private:
        using TimePoint = std::chrono::time_point <
            std::chrono::system_clock,
            std::chrono::duration <
                long,
                std::ratio <
                    1,
                    1000000000
                >
            >
        >;

        Time();
        void _proc();

        long long _tick;
        TimePoint _prevTime;
        float _deltaTime;
        long long _frameTick;
    };
}