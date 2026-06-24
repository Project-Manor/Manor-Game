#pragma once
#include "thing.hxx"
#include <registry>
#include <string>

namespace man::things {
    /**
     * @brief Create a Thing of type T.
     * @tparam T Type derived from man::things::Thing.
     * @param args Parameter pack, forwarded to Thing's constructor.
     * @return See man::registry::Reference for usage.
     */
    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createThing(Args &&...args);

    /**
     * @brief Create a Thing of type T with a unique tag.
     * @tparam T Type derived from man::things::Thing.
     * @param tag Unique per Thing, useful for a specific Thing retrieval.
     * @param args Parameter pack, forwarded to Thing's constructor.
     * @return See man::registry::Reference for usage.
     */
    template<ThingConcept T, typename ...Args>
    registry::Reference<T> createTaggedThing(std::string tag, Args &&...args);

    /**
     * @brief Get a Thing of type T.
     * @tparam T Type derived from man::things::Thing.
     * @param index Defaults to the first index (0).
     * Specifies which Thing index to return.
     * @return See man::registry::Reference for usage.
     */
    template<ThingConcept T>
    registry::Reference<T> getThing(std::size_t index = 0);

    /**
     * @brief Get a Thing of type T by it's tag.
     * @tparam T Type derived from man::things::Thing.
     * @param tag Unique per Thing, must be specified during creation.
     * See man::things::createTaggedThing.
     * @return See man::registry::Reference for usage.
     */
    template<ThingConcept T>
    registry::Reference<T> getTaggedThing(std::string tag);

    /**
     * @brief Get a range of Thing's of type T.\n
     * If the range is none (from = to), a single index is returned.
     * @tparam T Type derived from man::things::Thing.
     * @param from Start of range.\n
     * Clamped between first and last Thing index.
     * @param to End of range.\n
     * Clamped between first and last Thing index.
     * @return See std::vector, man::registry::Reference for usage.
     */
    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingRange (
        std::size_t from,
        std::size_t to
    );

    /**
     * @brief Get a range of Thing's of type T from the first index.\n
     * If the range is none (to = 0), the first index is returned.
     * @tparam T Type derived from man::things::Thing.
     * @param to End of range.\n
     * Clamped between first and last Thing index.
     * @return See std::vector, man::registry::Reference for usage.
     */
    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingPrefix(std::size_t to);

    /**
     * @brief Get a range of Thing's of type T up to the last index.\n
     * If the range is none (from = getThingCount()-1), the last index is returned.
     * @tparam T Type derived from man::things::Thing.
     * @param from Start of range.\n
     * Clamped between first and last Thing index.
     * @return See std::vector, man::registry::Reference for usage.
     */
    template<ThingConcept T>
    std::vector<registry::Reference<T>> getThingSuffix(std::size_t from);

    /**
     * @brief Get all Thing's of type T.\n
     * @tparam T Type derived from man::things::Thing.
     * @return See std::vector, man::registry::Reference for usage.
     */
    template<ThingConcept T>
    std::vector<registry::Reference<T>> getAllThings();

    /**
     * @brief Dynamically cast all Things to T Type if possible.
     * @tparam T Type derived from man::registry::Entry.
     * @return See std::vector, man::registry::Reference for usage.
     */
    template<ThingConcept T>
    std::vector<registry::Reference<T>> getAllThingsAs();

    /**
     * @tparam T Type derived from man::things::Thing.
     * @return The amount of Thing's of type T that exist.
     */
    template<ThingConcept T>
    std::size_t getThingCount();
}

namespace man::things {
    class RootThing final {
    friend class Thing;

    template<ThingConcept T, typename ...Args>
    friend registry::Reference<T> createThing(Args &&...args);

    template<ThingConcept T, typename ...Args>
    friend registry::Reference<T> createTaggedThing(std::string tag, Args &&...args);

    template<ThingConcept T>
    friend registry::Reference<T> getThing(std::size_t index);

    template<ThingConcept T>
    friend registry::Reference<T> getTaggedThing(std::string tag);

    template<ThingConcept T>
    friend std::vector<registry::Reference<T>> getThingRange (
        std::size_t from,
        std::size_t to
    );

    template<ThingConcept T>
    friend std::vector<registry::Reference<T>> getThingPrefix(std::size_t to);

    template<ThingConcept T>
    friend std::vector<registry::Reference<T>> getThingSuffix(std::size_t from);

    template<ThingConcept T>
    friend std::vector<registry::Reference<T>> getAllThings();

    template<ThingConcept T>
    friend std::vector<registry::Reference<T>> getAllThingsAs();

    template<ThingConcept T>
    friend std::size_t getThingCount();

    private:
        RootThing();
        ~RootThing();

    public:
        RootThing(const RootThing&) = delete;
        static RootThing &instance();

        static void process();
        static void terminate();

    private:
        registry::Registry _registry;
        static void _killThing(void *ptr);
    };
}

#include "root_thing.t.hxx"