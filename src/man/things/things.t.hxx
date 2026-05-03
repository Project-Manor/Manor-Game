#pragma once
#include "things.hxx"

template<typename T>
requires std::derived_from<T, man::things::Thing>
void man::Things::create() {
    T *t = new T;

    if (T::tag == UNTAGGED_THING) {
        instance()._uThingCtrs.emplace_back (
            t,
            [] (void *ptr) {
                static_cast<T*>(ptr)->process();
            },
            [] (void *ptr) {
                static_cast<T*>(ptr)->finish();
                delete static_cast<T*>(ptr);
            }
        );
    }
    else {
        instance()._tThingCtrs.insert ({
            T::tag,
            {
                t,
                [] (void *ptr) {
                    static_cast<T*>(ptr)->process();
                },
                [] (void *ptr) {
                    static_cast<T*>(ptr)->finish();
                    delete static_cast<T*>(ptr);
                }
            }
        });
    }

    static_cast<T*>(t)->launch();
}

template<typename T>
requires std::derived_from<T, man::things::Thing>
std::optional<std::reference_wrapper<T>> man::Things::getTagged() {
    Things &inst = instance();

    if (inst._tThingCtrs.contains(T::tag)) return {
        std::ref (
            *static_cast<T*>(inst._tThingCtrs[T::tag].ptr)
        )
    };

    return {std::nullopt};
}