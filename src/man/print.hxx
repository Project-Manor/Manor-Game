#pragma once

namespace man {
    constexpr void printspace(unsigned int count = 1);

    template<typename T, typename ...Args>
    constexpr void print(T t, Args ...args);

    template<typename ...Args>
    constexpr void println(Args ...args);

    template<typename ...Args>
    constexpr void printlns(Args ...args);
}

#include "print.t.hxx"