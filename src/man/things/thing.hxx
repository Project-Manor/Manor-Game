#pragma once
#include <string_view>

#define UNTAGGED_THING "UNTAGGED_THING"
#define TAG(name) static constexpr std::string_view tag = #name

namespace man {
    class Thing {
    public:
        Thing();
        virtual ~Thing();

        static constexpr std::string_view tag = UNTAGGED_THING;

        virtual void launch() = 0;
        virtual void process() = 0;
        virtual void finish() = 0;
    };
}