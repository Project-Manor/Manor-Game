#include "time.hxx"
#include <chrono>

namespace man {
    Time &Time::Time::instance() {
        static Time inst;
        return inst;
    }

    const long long &Time::tick() { return instance()._tick; }
    const float &Time::deltaTime() { return instance()._deltaTime; }

    const std::string Time::stringedData() {
        return std::format (
            "- Time Data -\nTick: {}\nDelta Time: {}\nAnimation Tick: {}\nAnimation FPS: {}\n",
            instance()._tick,
            instance()._deltaTime,
            instance()._animTick,
            instance()._animFPS
        );
    }

    Time::Time() :
        _startTime(std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0),
        _tick(0),
        _deltaTime(0),
        _animTick(0),
        _animFPS(8)
    {}

    void Time::_proc() {
        _tick++;

        _time = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000000000.0 - _startTime;
        _deltaTime = _time - _prevTime;
        _prevTime = _time;

        _animTick = _time / (1.0 / (double)_animFPS);
    }
}