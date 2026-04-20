#pragma once

namespace man::detail {
    void printspace(unsigned int count);

    template<typename T, typename ...Args>
    void print(T t, Args ...args);

    template<typename ...Args>
    void println(Args ...args);

    template<typename ...Args>
    void printlns(Args ...args);
}

#include "detail_print.t.hxx"