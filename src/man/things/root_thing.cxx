#include "root_thing.hxx"

namespace man::things {
    RootThing::RootThing() : _registry({}) {}
    RootThing::~RootThing() = default;

    RootThing &RootThing::instance() {
        static RootThing i;
        return i;
    }

    void RootThing::process() {
        instance()._registry.process();
    }

    void RootThing::terminate() {
        instance()._registry.terminate();
    }

    void RootThing::_killThing(void *ptr) {
        instance()._registry.dealloc(ptr);
    }
}