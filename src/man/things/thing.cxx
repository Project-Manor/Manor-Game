#include "thing.hxx"
#include "root_thing.hxx"

namespace man::things {
    Thing::Thing() :
        _inits({}),
        _procs({}),
        _terms({}),
        _activates({}),
        _deactivates({}),
        _registry({}),
        _parent(_pendingParent)
    {}

    Thing::~Thing() = default;

    void Thing::kill() {
        registry::Reference<Thing> p = getParentAs<Thing>();
        if (p)
            p->_registry.dealloc(this);
        else
            RootThing::_killThing(this);
    }

    void Thing::_initEntry() {
        for (const auto &fn : _inits)
            fn();
    }

    void Thing::_procEntry() {
        for (const auto &fn : _procs)
            fn();
        _registry.process();
    }

    void Thing::_termEntry() {
        _registry.terminate();
        for (const auto &fn : _terms)
            fn();
    }

    void Thing::_activateEntry() {
        for (const auto &fn : _activates)
            fn();

        for (registry::Reference<Thing> &c : _registry.getAllAs<Thing>())
            c->activate();
    }

    void Thing::_deactivateEntry() {
        for (const auto &fn : _deactivates)
            fn();

        for (registry::Reference<Thing> &c : _registry.getAllAs<Thing>())
            c->deactivate();
    }

    Thing::ParentScope::ParentScope(Thing *parent) :
        prev(_pendingParent)
    { _pendingParent = parent; }

    Thing::ParentScope::~ParentScope()
    { _pendingParent = prev; }

    thread_local Thing *Thing::_pendingParent = nullptr;
}