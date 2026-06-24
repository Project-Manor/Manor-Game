#pragma once
#include <vector>
#include <functional>
#include <string>
#include <registry>

namespace man::things {
    class Thing;

    template<typename T>
    concept ThingConcept =
        registry::EntryConcept<T>
    &&  std::derived_from<T, Thing>
    ;

    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createThing(Args &&...args);

    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createTaggedThing(std::string tag, Args &&...args);

    class Thing : public registry::Entry  {
    template<ThingConcept T, typename ...Args>
    friend registry::Reference<T> createThing(Args &&...args);

    template<ThingConcept T, typename ...Args>
    friend registry::Reference<T> createTaggedThing(std::string tag, Args &&...args);

    public:
        Thing();
        virtual ~Thing();

        /**
         * @brief Create a child Thing of type T.
         * @tparam T Type derived from man::things::Thing.
         * @param args Parameter pack, forwarded to Thing's constructor.
         * @return See man::registry::Reference for usage.
         */
        template<ThingConcept T, typename ...Args>
        registry::Reference<T> createChild(Args &&...args);

        /**
         * @brief Create a child Thing of type T with a unique tag.
         * @tparam T Type derived from man::things::Thing.
         * @param tag Unique per Thing, useful for a specific Thing retrieval.
         * @param args Parameter pack, forwarded to Thing's constructor.
         * @return See man::registry::Reference for usage.
         */
        template<ThingConcept T, typename ...Args>
        registry::Reference<T> createTaggedChild(std::string tag, Args &&...args);

        /**
         * @brief Get a child Thing of type T.
         * @tparam T Type derived from man::things::Thing.
         * @param index Defaults to the first index (0).
         * Specifies which Thing index to return.
         * @return See man::registry::Reference for usage.
         */
        template<ThingConcept T>
        registry::Reference<T> getChild(std::size_t index = 0);

        /**
         * @brief Get a child Thing of type T by it's tag.
         * @tparam T Type derived from man::things::Thing.
         * @param tag Unique per Thing, must be specified during creation.
         * See man::things::createTaggedThing.
         * @return See man::registry::Reference for usage.
         */
        template<ThingConcept T>
        registry::Reference<T> getTaggedChild(std::string tag);

        /**
         * @brief Get a range of child Thing's of type T.\n
         * If the range is none (from = to), a single index is returned.
         * @tparam T Type derived from man::things::Thing.
         * @param from Start of range.\n
         * Clamped between first and last child Thing index.
         * @param to End of range.\n
         * Clamped between first and last child Thing index.
         * @return See std::vector, man::registry::Reference for usage.
         */
        template<ThingConcept T>
        std::vector<registry::Reference<T>> getChildRange (
            std::size_t from,
            std::size_t to
        );

        /**
         * @brief Get a range of child Thing's of type T from the first index.\n
         * If the range is none (to = 0), the first index is returned.
         * @tparam T Type derived from man::things::Thing.
         * @param to End of range.\n
         * Clamped between first and last child Thing index.
         * @return See std::vector, man::registry::Reference for usage.
         */
        template<ThingConcept T>
        std::vector<registry::Reference<T>> getChildPrefix(std::size_t to);

        /**
         * @brief Get a range of child Thing's of type T up to the last index.\n
         * If the range is none (from = getChildCount()-1), the last index is returned.
         * @tparam T Type derived from man::things::Thing.
         * @param from Start of range.\n
         * Clamped between first and last child Thing index.
         * @return See std::vector, man::registry::Reference for usage.
         */
        template<ThingConcept T>
        std::vector<registry::Reference<T>> getChildSuffix(std::size_t from);

        /**
         * @brief Get all child Thing's of type T.\n
         * @tparam T Type derived from man::things::Thing.
         * @return See std::vector, man::registry::Reference for usage.
         */
        template<ThingConcept T>
        std::vector<registry::Reference<T>> getAllChildren();

        /**
         * @brief Dynamically cast all child Things to T Type if possible.
         * @tparam T Type derived from man::registry::Entry.
         * @return See std::vector, man::registry::Reference for usage.
         */
        template<ThingConcept T>
        std::vector<registry::Reference<T>> getAllChildrenAs();

        /**
         * @tparam T Type derived from man::things::Thing.
         * @return The amount of child Thing's of type T that exist.
         */
        template<ThingConcept T>
        std::size_t getChildCount();

        /**
         * @brief Get Thing's parent if it has one.\n
         * Uses man::registry::Reference::as() internally.
         * @return See man::registry::Reference for usage.
         */
        template<ThingConcept T>
        registry::Reference<T> getParentAs();

        /* @brief The Thing is destroyed, and it's memory cleaned up. */
        void kill();

    protected:
        /**
        * @brief Defines when and under what conditions the given system shall execute during a Thing's lifetime.
        */
        enum class SystemType {
            /* @brief Runs sequentially after Thing's creation. */
            Initialization,
            /* @brief Loops sequentially during Thing's lifetime. */
            Process,
            /* @brief Runs sequentially prior to Thing's destruction. */
            Termination,
            /**
            * @brief Runs sequentially after Thing's activation.
            * See man::registry::Entry for active state details.
            */
            Activation,
            /**
            * @brief Runs sequentially after Thing's deactivation.
            * See man::registry::Entry for active state details.
            */
            Deactivation
        };

        /**
        * @brief Add a system to execute during a Thing's lifetime.
        * This overload takes the address of an object, which is used in method passing.
        * If you pass a free function or lambda, this address is not used.
        * @tparam T Type derived from man::things::Thing.
        * @tparam ReqFn Type void (T::*)() or std::invocable.
        * @tparam Fns Parameter Pack of type void (T::*)() or std::invocable.
        * @param type See man::things::Thing::SystemType.
        * @param obj Address of the method owner, pass 'this'.
        * @param reqFn Pointer to the method, pass '&MyThing::myMethod'.
        * Alternatively pass a free function or lambda.
        * @param fns Same as 'reqFn', but optional and unlimited since it's a parameter pack.
        * Alternatively pass a free functions or lambdas.
        */
        template <
            ThingConcept T,
            typename ReqFn,
            typename ...Fns
        >
        requires (
            std::same_as<ReqFn, void (T::*)()>
        ||  std::invocable<ReqFn>
        )
        && ((
            std::same_as<Fns, void (T::*)()>
        ||  std::invocable<Fns>
        )&&...)
        void _addSystem (
            SystemType type,
            T *obj,
            ReqFn reqFn,
            Fns &&...fns
        );

        /**
        * @brief Add a system to execute during a Thing's lifetime.
        * This overload does not take the address of an object.
        * Only free functions or lambdas are allowed.
        * @tparam Fns Parameter Pack of type std::invocable.
        * @param type See man::things::Thing::SystemType.
        * @param reqFn Pass a free function or lambda.
        * @param fns Same as 'reqFn', but optional and unlimited since it's a parameter pack.
        */
        template<typename ...Fns>
        requires ((std::invocable<Fns>) &&...)
        void _addSystem (
            SystemType type,
            std::function<void()> reqFn,
            Fns &&...fns
        );

        template<typename T>
        [[deprecated("Use _addSystem() instead")]]
        void _addInit(T *obj, void (T::*meth)());

        template<typename T>
        [[deprecated("Use _addSystem() instead")]]
        void _addProc(T *obj, void (T::*meth)());

        template<typename T>
        [[deprecated("Use _addSystem() instead")]]
        void _addTerm(T *obj, void (T::*meth)());

    private:
        void _initEntry() override;
        void _procEntry() override;
        void _termEntry() override;
        void _activateEntry() override;
        void _deactivateEntry() override;

        std::vector<std::function<void()>> _inits;
        std::vector<std::function<void()>> _procs;
        std::vector<std::function<void()>> _terms;
        std::vector<std::function<void()>> _activates;
        std::vector<std::function<void()>> _deactivates;

        registry::Registry _registry;

        struct ParentScope {
            Thing *prev;
            ParentScope(Thing *parent);
            ~ParentScope();
        };
        static thread_local Thing *_pendingParent;
        registry::Reference<registry::Entry> _parent;
    };
}

#include "thing.t.hxx"