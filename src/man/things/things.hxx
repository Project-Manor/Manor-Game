#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <optional>
#include "thing.hxx"
#include "../core.hxx"

namespace man {
    class Things {
    public:
        Things(const Things&) = delete;
        static Things &instance();

        template<typename T>
        requires std::derived_from<T, man::Thing>
        static void create();

        template<typename T>
        requires std::derived_from<T, man::Thing>
        static std::optional<std::reference_wrapper<T>> getTagged();

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
            std::string_view,
            ThingContainer
        > _tThingCtrs;
    };
}

#include "things.t.hxx"