#pragma once
#include "root_thing.hxx"
#include <utility>

namespace man::things {
    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createThing(Args &&...args) {
        Thing::ParentScope scope{nullptr};
        return RootThing::instance()._registry.alloc<T>(std::forward<Args>(args)...);
    }

    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createTaggedThing(std::string tag, Args &&...args) {
        Thing::ParentScope scope{nullptr};
        return RootThing::instance()._registry.allocT<T>(tag, std::forward<Args>(args)...);
    }

    template<ThingConcept T>
    registry::Reference<T> getThing(std::size_t index) {
        return RootThing::instance()._registry.get<T>(index);
    }

    template<ThingConcept T>
    registry::Reference<T> getTaggedThing(std::string tag) {
        return RootThing::instance()._registry.getT<T>(tag);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingRange (
        std::size_t from,
        std::size_t to
    ) {
        return RootThing::instance()._registry.getRange<T>(from, to);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingPrefix(std::size_t to) {
        return RootThing::instance()._registry.getPrefix<T>(to);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingSuffix(std::size_t from) {
        return RootThing::instance()._registry.getSuffix<T>(from);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> getAllThings() {
        return RootThing::instance()._registry.getAll<T>();
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> getAllThingsAs() {
        return RootThing::instance()._registry.getAllAs<T>();
    }

    template<ThingConcept T>
    std::size_t getThingCount() {
        return RootThing::instance()._registry.count<T>();
    }
}