#include "time.hxx"

namespace man {
    Time &Time::Time::instance() {
        static Time inst;
        return inst;
    }

    const long long &Time::tick() { return instance()._tick; }
    const float &Time::deltaTime() { return instance()._deltaTime; }
    const long long &Time::frameTick() { return instance()._frameTick; }

    Time::Time() :
        _tick(0),
        _deltaTime(0),
        _frameTick(0)
    {}

    void Time::_proc() {
        _tick++;
        TimePoint time = std::chrono::high_resolution_clock::now();
        _deltaTime = std::chrono::duration<float>(time - _prevTime).count();
        _prevTime = time;
    }
}