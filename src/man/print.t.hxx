#pragma once
#include "print.hxx"
#include "core.hxx"
#include <iostream>
#include <format>

namespace man {
    constexpr void printspace(unsigned int count) {
        if constexpr (!kDebug) return;
        while (count --> 0)
            std::cout << '\n';
    }

    template<typename T, typename ...Args>
    constexpr void print(T t, Args ...args) {
        if constexpr (!kDebug) return;

        std::cout << std::format("{}", t);
        if constexpr (sizeof ...(Args) > 0) {
            print(args...);
        }
    }

    template<typename ...Args>
    constexpr void println(Args ...args) {
        if constexpr (!kDebug) return;
        print(args..., "\n");
    }

    template<typename ...Args>
    constexpr void printlns(Args ...args) {
        if constexpr (!kDebug) return;
        ((print(std::format("{}\n", args))), ...);
    }
}