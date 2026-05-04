#pragma once

namespace man::things {
    class Thing {
    public:
        Thing();
        virtual ~Thing();

        virtual void launch() = 0;
        virtual void process() = 0;
        virtual void finish() = 0;
    };
}