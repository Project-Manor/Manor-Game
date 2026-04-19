#pragma once
#include "core.hxx"

namespace man {
    class Time {
        public:
            Time(const Time&) = delete;
            static Time &instance();

            static const long long &time();
            static const double &deltaTime();
            static const long long &frameTick();

        friend void man::init();
        friend bool man::proc();

        private:
            Time();
            void _proc();

            long long _time;
            double _deltaTime;
            long long _frameTick;
    };
}