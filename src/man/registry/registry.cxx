#include "registry.hxx"

namespace man::registry {
    Registry::Registry() :
        _processing(false),
        _terminationRequested(false),
        _terminated(false),
        _pendingDeallocs({}),
        _ctrs({}),
        _ctrPtrToType({}),
        _registeredTags({})
    {}

    Registry::~Registry() = default;

    void Registry::process() {
        _processing = true;

        for (const auto &[type, containers] : _ctrs) {
            for (const Container &ctr : containers) {
                if (static_cast<Entry*>(ctr.ptr)->isActive())
                    ctr.proc();
            }
        }

        _processing = false;

        for (auto &fn : _pendingAllocs) fn();
        for (auto &[ptr, fn] : _pendingDeallocs) fn();

        _pendingAllocs.clear();
        _pendingDeallocs.clear();

        if (_terminationRequested)
            terminate();
    }

    void Registry::terminate() {
        if (_terminated) return;

        if (_processing) {
            _terminationRequested = true;
            return;
        }

        _terminated = true;

        for (const auto &[type, containers] : _ctrs) {
            for (const Container &ctr : containers)
                ctr.del();
        }

        _ctrs.clear();
        _ctrPtrToType.clear();
        _registeredTags.clear();
    }

    void Registry::dealloc(void *ptr) {
        if (_terminated) return;

        if (_processing) {
            if (!_pendingDeallocs.contains(ptr))
                _pendingDeallocs.emplace (
                    ptr,
                    [this, ptr]() { dealloc(ptr); }
                );

            return;
        }

        std::type_index type = _ctrPtrToType.at(ptr);
        int index = 0;

        for (Container &ctr : _ctrs[type]) {
            if (ptr == ctr.ptr) goto guillotine;
            index++;
        }
        return;

        guillotine:
        std::vector<Container> &v = _ctrs[type];

        if (std::optional<std::string> &tag = static_cast<Entry*>(v[index].ptr)->_tag;
            tag
        &&  _registeredTags.contains(tag.value())
        ) _registeredTags.erase(tag.value());

        v[index].del();
        v.erase(v.begin() + index);

        if (0 == v.size())
            _ctrs.erase(type);

        _ctrPtrToType.erase(ptr);
    }
}