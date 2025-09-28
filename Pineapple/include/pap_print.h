#pragma once

#include <iostream>

#ifdef __cpp_lib_print
#include <print>
#define PAP_PRINT(...) std::print(__VA_ARGS__)
#else
#include <format>
namespace pap{
    template<typename... Args>
    void print(const std::string& fmt, Args&&... args) {
        std::cout << std::format(fmt, std::forward<Args>(args)...);
    }
}
#define PAP_PRINT(...) pap::print(__VA_ARGS__)
#endif
