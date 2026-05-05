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

        virtual void init() = 0;

        virtual void launch();
        virtual void process();
        virtual void finish();

    protected:
        template<typename T>
        void _addInit(T *obj, void (T::*meth)()) const {
            _inits.emplace_back(std::bind_front(meth, obj));
        }

        template<typename T>
        void _addProc(T *obj, void (T::*meth)()) const {
            _procs.emplace_back(std::bind_front(meth, obj));
        }

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