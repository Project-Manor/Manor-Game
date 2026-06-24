#pragma once
#include <unordered_map>
#include <functional>
#include <optional>
#include <string>

namespace man::registry {
    class Entry;

    template<typename T>
    concept EntryConcept = std::derived_from<T, Entry>;

    class Registry;

    template<EntryConcept T>
    class Reference;
}

namespace man::registry {
    class Entry {
    friend class Registry;

    template<EntryConcept T>
    friend class Reference;

    protected:
        Entry();

    public:
        virtual ~Entry();

        /**
         * @brief Check if an Entry is active for processing.
         * @retval true Entry is active, will process.
         * @retval false Entry is not active, will not process.
         */
        bool isActive();

        /**
         * @brief Set Entry's active state.
         * @param state\n
         * true: Activate processing for Entry.\n
         *       Equivalent to activate().\n\n
         * false: Deactivate processing for Entry.\n
         *        Equivalent to deactivate().
         */
        void setActive(bool state);

        /**
         * @brief Activate processing for Entry.\n
         * Equivalent to setActive(true).
         */
        void activate();

        /**
         * @brief Deactivate processing for Entry.\n
         * Equivalent to setActive(false).
         */
        void deactivate();

    protected:
        virtual void _initEntry() = 0;
        virtual void _procEntry() = 0;
        virtual void _termEntry() = 0;
        virtual void _activateEntry() = 0;
        virtual void _deactivateEntry() = 0;

    private:
        std::unordered_map <
            void*,
            std::function<void()>
        > _refs;

        std::optional<std::string> _tag;
        bool _activeState;

        void _addRef (
            void *ptr,
            std::function<void()> nullify
        );

        void _rmRef(void *ptr);
    };
}