#pragma once
#include <concepts>
#include <vector>
#include <functional>
#include <unordered_map>

namespace man {
    class Things;

    namespace things {
        class Thing;

        template<typename T>
        requires std::derived_from<T, Thing>
        class ThingRef;
    }
}

namespace man::things {
    class Thing {
    friend class man::Things;

    template<typename T>
    requires std::derived_from<T, Thing>
    friend class man::things::ThingRef;

    public:
        Thing();
        virtual ~Thing();

    protected:
        /**
        *   @brief Add a Initialization function, runs sequentially on Thing's creation
        *   @param obj Pointer to the method owner, pass 'this'
        *   @param meth Pointer to the method, pass '&MyThing::myMethod'
        */
        template<typename T>
        void _addInit(T *obj, void (T::*meth)()) const {
            _inits.emplace_back(std::bind_front(meth, obj));
        }

        /**
        *   @brief Add a Process function, loops sequentially during Thing's lifetime
        *   @param obj Pointer to the method owner, pass 'this'
        *   @param meth Pointer to the method, pass '&MyThing::myMethod'
        */
        template<typename T>
        void _addProc(T *obj, void (T::*meth)()) const {
            _procs.emplace_back(std::bind_front(meth, obj));
        }

        /**
        *   @brief Add a Termination function, runs sequentially on Thing's destruction
        *   @param obj Pointer to the method owner, pass 'this'
        *   @param meth Pointer to the method, pass '&MyThing::myMethod'
        */
        template<typename T>
        void _addTerm(T *obj, void (T::*meth)()) const {
            _terms.emplace_back(std::bind_front(meth, obj));
        }

    private:
        mutable std::vector<std::function<void()>> _inits;
        mutable std::vector<std::function<void()>> _procs;
        mutable std::vector<std::function<void()>> _terms;

        std::unordered_map <
            void*,
            std::function<void(void*, bool)>
        > _refs;

        void _addRef(void *ptr, std::function<void(void*, bool)> fn);
        void _rmRef(void *ptr);
    };
}