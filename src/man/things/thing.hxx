#pragma once
#include <vector>
#include <functional>

namespace man {
    class Things;
}

namespace man::things {
    class Thing {
    friend class man::Things;
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
    };
}