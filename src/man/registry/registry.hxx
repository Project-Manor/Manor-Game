#pragma once
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <vector>
#include <string>
#include <set>
#include "entry.hxx"
#include "reference.hxx"

namespace man::registry {
    class Registry final {
    public:
        Registry();
        ~Registry();

        void process();
        void terminate();

        template<EntryConcept T, typename ...Args>
        Reference<T> alloc(Args &&...args);

        template<EntryConcept T, typename ...Args>
        Reference<T> allocT(std::string tag, Args &&...args);

        template<EntryConcept T>
        Reference<T> get(std::size_t index = 0);

        template<EntryConcept T>
        Reference<T> getT(std::string tag);

        template<EntryConcept T>
        std::vector<Reference<T>> getRange (
            std::size_t from,
            std::size_t to
        );

        template<EntryConcept T>
        std::vector<Reference<T>> getPrefix(std::size_t to);

        template<EntryConcept T>
        std::vector<Reference<T>> getSuffix(std::size_t from);

        template<EntryConcept T>
        std::vector<Reference<T>> getAll();

        template<EntryConcept T>
        std::vector<Reference<T>> getAllAs();

        template<EntryConcept T>
        std::size_t count();

        void dealloc(void *ptr);

    private:
        bool _processing;
        bool _terminationRequested;
        bool _terminated;

        std::vector<std::function<void()>> _pendingAllocs;

        std::unordered_map <
            void*,
            std::function<void()>
        > _pendingDeallocs;

        struct Container {
            void *ptr;
            std::function<void()> proc;
            std::function<void()> del;
        };

        std::unordered_map <
            std::type_index,
            std::vector<Container>
        > _ctrs;

        std::unordered_map <
            void*,
            std::type_index
        > _ctrPtrToType;

        std::set<std::string> _registeredTags;
    };
}

#include "registry.t.hxx"