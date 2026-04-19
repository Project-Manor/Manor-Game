#pragma once

namespace man {
    class Time {
        public:
            Time();
            ~Time();

            void proc();

            const double time;
            const double deltaTime;
            const int animTick;
    };
}