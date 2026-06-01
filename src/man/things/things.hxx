#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>
#include "thing.hxx"
#include "thing_ref.hxx"
#include "../core.hxx"

namespace man {
    class Things {
    public:
        Things(const Things&) = delete;
        static Things &instance();

        template<typename T>
        requires std::derived_from<T, man::things::Thing>
        static const man::things::ThingRef<T> create();

        template<typename T>
        requires std::derived_from<T, man::things::Thing>
        static const man::things::ThingRef<T> create(std::string tag);

        template<typename T>
        requires std::derived_from<T, man::things::Thing>
        static const man::things::ThingRef<T> getTagged(std::string tag);

    friend bool man::proc();

    private:
        Things();
        ~Things();

        void _proc();

        struct ThingContainer {
            void *ptr;
            std::function<void(void*)> proc;
            std::function<void(void*)> del;
        };

        std::vector<ThingContainer> _uThingCtrs;

        std::unordered_map <
            std::string,
            ThingContainer
        > _tThingCtrs;
    };
}

#include "things.t.hxx"