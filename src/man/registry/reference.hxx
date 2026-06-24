#pragma once
#include "entry.hxx"

namespace man::registry {
    /**
     * @brief A weak reference to a man::registry::Entry.
     * Does not own or manage the actual entry.
     * @tparam T Type derived from man::registry::Entry.
     */
    template<EntryConcept T>
    class Reference final {
    public:
        Reference(T *ptr);
        ~Reference();
        Reference(const Reference &other);
        Reference &operator=(const Reference &other);
        Reference(Reference &&other) noexcept;
        Reference &operator=(Reference &&other) noexcept;

        /**
         * @retval true Entry exists, safe to access.
         * @retval false Entry is null, do not access.
         */
        bool exists();

        /* @brief Equivalent to exists(). */
        explicit operator bool();

        /**
         * @return The Entry's memory address.
         * May return nullptr, always ensure validity using exists().
         */
        T *const get();

        /* @brief Equivalent to get(). */
        T *const operator->();

        /**
         * @brief Dynamically cast the Entry to U Type if possible.
         * @tparam U Type derived from man::registry::Entry.
         * @return A new Reference of type U.
         * Always check it's validity using exists().
         */
        template<EntryConcept U>
        Reference<U> as();

    private:
        T *_ptr;
    };
}

#include "reference.t.hxx"