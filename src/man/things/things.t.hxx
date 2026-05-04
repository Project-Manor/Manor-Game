#pragma once
#include "things.hxx"
#include "../print.hxx"

template<typename T>
requires std::derived_from<T, man::things::Thing>
std::optional<std::reference_wrapper<T>> man::Things::create() {
    T *t = new T;
    static_cast<T*>(t)->launch();

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

    return std::ref (
        *static_cast<T*>(instance()._uThingCtrs.back().ptr)
    );
}

template<typename T>
requires std::derived_from<T, man::things::Thing>
std::optional<std::reference_wrapper<T>> man::Things::create(std::string tag) {
    if (instance()._tThingCtrs.contains(tag)) {
        printspace();
        println("Things Error: A thing with tag '", tag, "' already exists!");
        println("            : Thing was not created.");
        printspace();
        return {std::nullopt};
    }

    T *t = new T;
    static_cast<T*>(t)->launch();

    instance()._tThingCtrs.insert ({
        tag,
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

    return std::ref (
        *static_cast<T*>(instance()._tThingCtrs[tag].ptr)
    );
}

template<typename T>
requires std::derived_from<T, man::things::Thing>
std::optional<std::reference_wrapper<T>> man::Things::getTagged(std::string tag) {
    if (instance()._tThingCtrs.contains(tag)) return {
        std::ref (
            *static_cast<T*>(instance()._tThingCtrs[tag].ptr)
        )
    };

    printspace();
    println("Things Warning: A thing with tag '", tag, "' does not exist!");
    println("              : Returning 'null option'.");
    printspace();
    return {std::nullopt};
}