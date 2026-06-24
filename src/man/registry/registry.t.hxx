#pragma once
#include "registry.hxx"
#include <utility>
#include <algorithm>

namespace man::registry {
    template<EntryConcept T, typename ...Args>
    Reference<T> Registry::alloc(Args &&...args) {
        if (_terminated) return { static_cast<T*>(nullptr) };

        T *t = new T{std::forward<Args>(args)...};
        static_cast<Entry *const>(t)->_initEntry();

        auto commit = [this, t]() {
            _ctrPtrToType.emplace(t, typeid(T));
            _ctrs[typeid(T)].emplace_back (
                t,
                [t] () {
                    static_cast<Entry *const>(t)->_procEntry();
                },
                [t] () {
                    static_cast<Entry *const>(t)->_termEntry();
                    delete static_cast<T *const>(t);
                }
            );
        };

        if (_processing) _pendingAllocs.emplace_back(commit);
        else commit();

        return { t };
    }

    template<EntryConcept T, typename ...Args>
    Reference<T> Registry::allocT(std::string tag, Args &&...args) {
        if (_terminated) return { static_cast<T*>(nullptr) };

        if (_registeredTags.contains(tag))
            return Reference<T> {
                static_cast<T*>(nullptr)
            };

        Reference<T> t = alloc<T>(std::forward<Args>(args)...);
        t->_tag = {tag};
        _registeredTags.emplace(tag);

        return t;
    }

    template<EntryConcept T>
    Reference<T> Registry::get(std::size_t index) {
        if (!_ctrs.contains(typeid(T))
        ||  index >= _ctrs[typeid(T)].size()
        ) return Reference<T> {
            static_cast<T*>(nullptr)
        };

        return Reference<T> {
            static_cast<T*> (
                _ctrs[typeid(T)][index].ptr
            )
        };
    }

    template<EntryConcept T>
    Reference<T> Registry::getT(std::string tag) {
        if (!_registeredTags.contains(tag))
            goto returnNull;

        for (Container &ctr : _ctrs[typeid(T)]) {
            if (T *p = static_cast<T*>(ctr.ptr);
                !p->_tag
            ||  p->_tag.value() != tag
            ) continue;

            return Reference<T> {
                static_cast<T*>(ctr.ptr)
            };
        }

        returnNull:
        return Reference<T> {
            static_cast<T*>(nullptr)
        };
    }

    template<EntryConcept T>
    std::vector<Reference<T>> Registry::getRange (
        std::size_t from,
        std::size_t to
    ) {
        if (!_ctrs.contains(typeid(T))) return {};

        from = std::clamp(from, std::size_t{0}, count<T>()-1);
        to = std::clamp(to, std::size_t{0}, count<T>()-1);
        if (from == to) return { get<T>(from) };

        std::vector<Reference<T>> v = {};

        std::vector<Container> &ctrs = _ctrs[typeid(T)];
        for (std::size_t i = from; i <= to; i++)
            v.emplace_back (
                static_cast<T*>(ctrs[i].ptr)
            );

        return v;
    }

    template<EntryConcept T>
    std::vector<Reference<T>> Registry::getPrefix(std::size_t to) {
        return getRange<T>(0, to);
    }

    template<EntryConcept T>
    std::vector<Reference<T>> Registry::getSuffix(std::size_t from) {
        return getRange<T>(from, count<T>()-1);
    }

    template<EntryConcept T>
    std::vector<Reference<T>> Registry::getAll() {
        return getRange<T>(0, count<T>()-1);
    }

    template<EntryConcept T>
    std::vector<Reference<T>> Registry::getAllAs() {
        std::vector<Reference<T>> v = {};

        for (auto &[type, ctrs] : _ctrs)
            for (auto &ctr : ctrs) {
                T *ptr = dynamic_cast<T*> (
                    static_cast<Entry*>(ctr.ptr)
                );

                if (!ptr) continue;

                v.emplace_back(ptr);
            }

        return v;
    }

    template<EntryConcept T>
    std::size_t Registry::count() {
        return !_ctrs.contains(typeid(T))
            ? 0
            : _ctrs[typeid(T)].size()
        ;
    }
}