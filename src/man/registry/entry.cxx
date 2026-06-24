#include "entry.hxx"

namespace man::registry {
    Entry::Entry() :
        _tag(std::nullopt),
        _activeState(true)
    {}

    Entry::~Entry() {
        for (const auto &[ptr, fn] : _refs) {
            fn();
        }
    }

    bool Entry::isActive()
    { return _activeState; }

    void Entry::setActive(bool state) {
        state ? activate() : deactivate();
    }

    void Entry::activate() {
        _activeState = true;
        _activateEntry();
    }

    void Entry::deactivate() {
        _activeState = false;
        _deactivateEntry();
    }

    void Entry::_addRef (
        void *ptr,
        std::function<void()> nullify
    ) {
        _refs[ptr] = nullify;
    }

    void Entry::_rmRef(void *ptr) {
        _refs.erase(ptr);
    }
}