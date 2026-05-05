#pragma once
#include <concepts>
#include "thing.hxx"

namespace man::things {
    template<typename T>
    requires std::derived_from<T, man::things::Thing>
    class ThingRef {
    public:
        ThingRef(bool exists, T *ptr = nullptr) :
            _exists(exists),
            _ptr(ptr)
        {}

        const bool exists() const { return _exists; }
        explicit operator bool() const { return exists(); }

        T *const get() const { return _ptr; }
        T *const operator->() const { return get(); }

    private:
        bool _exists;
        T *const _ptr;
    };
}