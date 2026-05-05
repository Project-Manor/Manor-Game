#pragma once
#include "things.hxx"
#include "../print.hxx"
#include "../str_colour.hxx"

template<typename T>
requires std::derived_from<T, man::things::Thing>
const man::things::ThingRef<T> man::Things::create() {
    T *t = new T;
    for (std::function<void()> &fn : static_cast<T*>(t)->_inits)
        fn();

    instance()._uThingCtrs.emplace_back (
        t,
        [] (void *ptr) {
            for (std::function<void()> &fn : static_cast<T*>(ptr)->_procs)
                fn();
        },
        [] (void *ptr) {
            for (std::function<void()> &fn : static_cast<T*>(ptr)->_terms)
                fn();
            delete static_cast<T*>(ptr);
        }
    );

    return {true, t};
}

template<typename T>
requires std::derived_from<T, man::things::Thing>
const man::things::ThingRef<T> man::Things::create(std::string tag) {
    if (instance()._tThingCtrs.contains(tag)) {
        printspace();
        println(man::strYellow("| Things Warning:"), " A thing with tag ", man::strCyan(tag), " already exists!");
        println(man::strYellow("|"), " Thing was not created, returning ", man::strCyan("NULLED ThingRef"));
        printspace();
        return {false};
    }

    T *t = new T;
    for (std::function<void()> &fn : static_cast<T*>(t)->_inits)
        fn();

    instance()._tThingCtrs.insert ({
        tag,
        {
            t,
            [] (void *ptr) {
                for (std::function<void()> &fn : static_cast<T*>(ptr)->_procs)
                    fn();
            },
            [] (void *ptr) {
                for (std::function<void()> &fn : static_cast<T*>(ptr)->_terms)
                    fn();
                delete static_cast<T*>(ptr);
            }
        }
    });

    return {true, t};
}

template<typename T>
requires std::derived_from<T, man::things::Thing>
const man::things::ThingRef<T> man::Things::getTagged(std::string tag) {
    if (instance()._tThingCtrs.contains(tag)) return {
        true,
        static_cast<T*>(instance()._tThingCtrs[tag].ptr)
    };

    printspace();
    println(man::strYellow("| Things Warning:"), " A thing with tag ", man::strCyan(tag), " does not exist!");
    println(man::strYellow("|"), " Returning ", man::strCyan("NULLED ThingRef"));
    printspace();

    return {false};
}