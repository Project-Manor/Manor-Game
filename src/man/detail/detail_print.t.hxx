#pragma once
#include "detail_print.hxx"
#include <iostream>
#include <format>

inline void man::detail::printspace(unsigned int count = 1) {
    while (count --> 0) {
        std::cout << '\n';
    }
}

template<typename T, typename ...Args>
void man::detail::print(T t, Args ...args) {
    std::cout << std::format("{}", t);
    if constexpr (sizeof ...(Args) > 0) {
        print(args...);
    }
}

template<typename ...Args>
void man::detail::println(Args ...args) {
    print(args..., "\n");
}

template<typename ...Args>
void man::detail::printlns(Args ...args) {
    ((print(std::format("{}\n", args))), ...);
}