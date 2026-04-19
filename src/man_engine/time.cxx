#include "time.hxx"

namespace man {
    Time &Time::Time::instance() {
        static Time inst;
        return inst;
    }

    const long long &Time::time() { return instance()._time; }
    const double &Time::deltaTime() { return instance()._deltaTime; }
    const long long &Time::frameTick() { return instance()._frameTick; }

    Time::Time() :
        _time(0),
        _deltaTime(0),
        _frameTick(0)
    {}

    void Time::_proc() {}
}