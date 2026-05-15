#include "thing.hxx"
#include "../print.hxx"

man::things::Thing::Thing() :
    _inits(0),
    _procs(0),
    _terms(0)
{}

man::things::Thing::~Thing() {
    for (auto &[ptr, fn] : _refs)
        fn(ptr, false);
}

void man::things::Thing::_addRef (
    void *ptr,
    std::function<void(void*, bool)> fn
) {
    _refs.insert({ptr, fn});
}

void man::things::Thing::_rmRef(void *ptr) {
    if (!_refs.contains(ptr)) return;
    _refs.erase(ptr);
}