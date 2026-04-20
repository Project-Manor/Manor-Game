#pragma once
#include "detail/detail_print.hxx"

// Print multiple newlines
// unsigned int 'count'
#define printspace(count) man::detail::printspace(count)

// Print all arguments
#define print(...) man::detail::print(__VA_ARGS__)

// Print all arguments, followed by a newline
#define println(...) man::detail::println(__VA_ARGS__)

// Print all arguments, each on a newline
#define printlns(...) man::detail::printlns(__VA_ARGS__)