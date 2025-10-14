#pragma once
#include <cassert>
#include <expected>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <cstring>

//just some core utilites that should be included in most files


namespace pap
{


} // namespace pap

#ifdef __cpp_lib_print
#include <print>
#define PAP_PRINT(...)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        std::println(__VA_ARGS__);                                                                                     \
    } while (0)
#else
namespace pap
{
constexpr void print(const std::string_view str_fmt, auto&&... args ){
    fputs(std::vformat(str_format, std::make_format_args(args...)).c_str(), stdout)
}
} // namespace pap
#define PAP_PRINT(...)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        pap::println(__VA_ARGS__);                                                                                     \
    } while (0)
#endif

#ifdef PAP_DEBUG
// ANSI color codes
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_PINK "\033[95m"

// Helper macro to extract filename from full path
#define FILENAME(msg) (strrchr(msg, '/') ? strrchr(msg, '/') + 1 : msg)

#ifdef PINEAPPLE_LIB
#define PAP_LOG_LEVEL_NAME "CORE"
#else
#define PAP_LOG_LEVEL_NAME "CLIENT"
#endif

#define PAP_LOG(level_color, level_name, ...)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        std::string _log_msg = std::format(__VA_ARGS__);                                                               \
        PAP_PRINT(level_color "[{}:{}] [{}] {}" COLOR_RESET "\n", FILENAME(__FILE__), __LINE__, level_name, _log_msg); \
    } while (0)

#define PAP_TRACE(...) PAP_LOG(COLOR_BLUE, PAP_LOG_LEVEL_NAME "/TRACE", __VA_ARGS__)
#define PAP_INFO(...) PAP_LOG(COLOR_GREEN, PAP_LOG_LEVEL_NAME "/INFO", __VA_ARGS__)
#define PAP_WARN(...) PAP_LOG(COLOR_YELLOW, PAP_LOG_LEVEL_NAME "/WARN", __VA_ARGS__)
#define PAP_ERROR(...) PAP_LOG(COLOR_RED, PAP_LOG_LEVEL_NAME "/ERROR", __VA_ARGS__)
#define PAP_CRITICAL(...) PAP_LOG(COLOR_PINK, PAP_LOG_LEVEL_NAME "/CRITICAL", __VA_ARGS__)

#else

#define PAP_LOG(level_color, level_name, ...)
#define PAP_TRACE(...)
#define PAP_INFO(...)
#define PAP_WARN(...)
#define PAP_ERROR(...)
#define PAP_CRITICAL(...)


#endif
