#pragma once
#include "thing.hxx"
#include <utility>

namespace man::things {
    template<ThingConcept T, typename ...Args>
    registry::Reference<T> Thing::createChild(Args &&...args) {
        ParentScope scope{this};
        registry::Reference<T> t = _registry.alloc<T>(std::forward<Args>(args)...);
        return t;
    }

    template<ThingConcept T, typename ...Args>
    registry::Reference<T> Thing::createTaggedChild(std::string tag, Args &&...args) {
        ParentScope scope{this};
        registry::Reference<T> t = _registry.allocT<T>(tag, std::forward<Args>(args)...);
        return t;
    }

    template<ThingConcept T>
    registry::Reference<T> Thing::getChild(std::size_t index) {
        return _registry.get<T>(index);
    }

    template<ThingConcept T>
    registry::Reference<T> Thing::getTaggedChild(std::string tag) {
        return _registry.getT<T>(tag);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> Thing::getChildRange (
        std::size_t from,
        std::size_t to
    ) {
        return _registry.getRange<T>(from, to);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> Thing::getChildPrefix(std::size_t to) {
        return _registry.getPrefix<T>(to);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> Thing::getChildSuffix(std::size_t from) {
        return _registry.getSuffix<T>(from);
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> Thing::getAllChildren() {
        return _registry.getAll<T>();
    }

    template<ThingConcept T>
    std::vector<registry::Reference<T>> Thing::getAllChildrenAs() {
        return _registry.getAllAs<T>();
    }

    template<ThingConcept T>
    std::size_t Thing::getChildCount() {
        return _registry.count<T>();
    }

    template<ThingConcept T>
    registry::Reference<T> Thing::getParentAs() {
        return _parent.as<T>();
    }

    template <
        ThingConcept T,
        typename ReqFn,
        typename ...Fns
    >
    requires (
        std::same_as<ReqFn, void (T::*)()>
    ||  std::invocable<ReqFn>
    )
    && ((
        std::same_as<Fns, void (T::*)()>
    ||  std::invocable<Fns>
    )&&...)
    void Thing::_addSystem (
        SystemType type,
        T *obj,
        ReqFn reqFn,
        Fns &&...fns
    ) {
        std::vector<std::function<void()>> *v = nullptr;

        switch (type) {
            default: return;
            case SystemType::Initialization: v = &_inits; break;
            case SystemType::Process: v = &_procs; break;
            case SystemType::Termination: v = &_terms; break;
            case SystemType::Activation: v = &_activates; break;
            case SystemType::Deactivation: v = &_deactivates; break;
        }

        if constexpr (std::same_as<ReqFn, void (T::*)()>)
            v->emplace_back(std::bind_front(reqFn, obj));
        else
            v->emplace_back(reqFn);

        (
            [&] {
                if constexpr (std::same_as<Fns, void (T::*)()>)
                    v->emplace_back(std::bind_front(fns, obj));
                else
                    v->emplace_back(fns);
            }(),
            ...
        );
    }

    template<typename ...Fns>
    requires ((std::invocable<Fns>)&&...)
    void Thing::_addSystem (
        SystemType type,
        std::function<void()> reqFn,
        Fns &&...fns
    ) {
        _addSystem(type, this, reqFn, std::forward<Fns>(fns)...);
    }

    template<typename T>
    void Thing::_addInit(T *obj, void (T::*meth)()) {
        _addSystem(SystemType::Initialization, obj, meth);
    }

    template<typename T>
    void Thing::_addProc(T *obj, void (T::*meth)()) {
        _addSystem(SystemType::Process, obj, meth);
    }

    template<typename T>
    void Thing::_addTerm(T *obj, void (T::*meth)()) {
        _addSystem(SystemType::Termination, obj, meth);
    }
}