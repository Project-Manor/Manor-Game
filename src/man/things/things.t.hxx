#pragma once
#include "things.hxx"
#include "../print.hxx"
#include "../str_colour.hxx"

template<typename T>
requires std::derived_from<T, man::things::Thing>
std::optional<std::reference_wrapper<T>> man::Things::create() {
    T *t = new T;
    static_cast<T*>(t)->init();
    static_cast<T*>(t)->launch();

    for (std::function<void()> &fn : static_cast<T*>(t)->_inits)
        fn();

    instance()._uThingCtrs.emplace_back (
        t,
        [] (void *ptr) {
            static_cast<T*>(ptr)->process();
            for (std::function<void()> &fn : static_cast<T*>(ptr)->_procs)
                fn();
        },
        [] (void *ptr) {
            static_cast<T*>(ptr)->finish();
            for (std::function<void()> &fn : static_cast<T*>(ptr)->_terms)
                fn();
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
        println(man::strRed("| Things Error:"), " A thing with tag ", man::strCyan(tag), " already exists!");
        println(man::strRed("|"), " Thing was not created, returning ", man::strCyan("null option"));
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
    println(man::strYellow("| Things Warning:"), " A thing with tag ", man::strCyan(tag), " does not exist!");
    println(man::strYellow("|"), " Returning ", man::strCyan("null option"));
    printspace();
    return {std::nullopt};
}