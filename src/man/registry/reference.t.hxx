#pragma once
#include "reference.hxx"

namespace man::registry {
    template<EntryConcept T>
    Reference<T>::Reference(T *ptr) :
        _ptr(ptr)
    {
        if (!_ptr) return;
        _ptr->_addRef(this, [this]() { _ptr = nullptr; });
    }

    template<EntryConcept T>
    Reference<T>::~Reference() {
        if (!_ptr) return;
        _ptr->_rmRef(this);
    }

    template<EntryConcept T>
    Reference<T>::Reference(const Reference &other) :
        Reference(other._ptr)
    {}

    template<EntryConcept T>
    Reference<T> &Reference<T>::operator=(const Reference &other) {
        if (this == &other) return *this;

        if (_ptr) _ptr->_rmRef(this);
        _ptr = other._ptr;
        if (_ptr) _ptr->_addRef(this, [this]() { _ptr = nullptr; });

        return *this;
    }

    template<EntryConcept T>
    Reference<T>::Reference(Reference &&other) noexcept :
        _ptr(other._ptr)
    {
        if (_ptr) {
            _ptr->_rmRef(&other);
            _ptr->_addRef(this, [this]() { _ptr = nullptr; });
        }

        other._ptr = nullptr;
    }

    template<EntryConcept T>
    Reference<T> &Reference<T>::operator=(Reference &&other) noexcept {
        if (this == &other) return *this;
        if (_ptr) _ptr->_rmRef(this);
        _ptr = other._ptr;

        if (_ptr) {
            _ptr->_rmRef(&other);
            _ptr->_addRef(this, [this]() { _ptr = nullptr; });
        }

        other._ptr = nullptr;
        return *this;
    }

    template<EntryConcept T>
    bool Reference<T>::exists()
    { return _ptr; }

    template<EntryConcept T>
    Reference<T>::operator bool()
    { return exists(); }

    template<EntryConcept T>
    T *const Reference<T>::get() {
        return static_cast<T *const>(_ptr);
    }

    template<EntryConcept T>
    T *const Reference<T>::operator->()
    { return _ptr; }

    template<EntryConcept T>
    template<EntryConcept U>
    Reference<U> Reference<T>::as() {
        return { dynamic_cast<U*>(_ptr) };
    }
}