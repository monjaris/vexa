#pragma once
#include <print>
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(log)


namespace internal {
    inline bool logging_enabled = true;
}
namespace intern = internal;


inline void setEnabled(bool yes) {
    intern::logging_enabled = yes;
}

[[nodiscard]] inline bool isEnabled() {
    return intern::logging_enabled;
}


static constexpr const char* const PRINT_PREFIX = "";
static constexpr const char* const PRINT_POSTFIX = "\n";

static constexpr const char* const INFO_PREFIX    = "\033[36m[INFO]\033[0m ";
static constexpr const char* const INFO_POSTFIX   = "\n";
//
static constexpr const char* const WARNING_PREFIX = "\033[33m[WARN]\033[0m ";
static constexpr const char* const WARNING_POSTFIX = "\n";
//
static constexpr const char* const ERROR_PREFIX   = "\033[1;35m[ERROR]\033[0m ";
static constexpr const char* const ERROR_POSTFIX  = "\n";
//
static constexpr const char* const FATAL_PREFIX   = "\033[1;31m[FATAL]\033[0m ";
static constexpr const char* const FATAL_POSTFIX  = "!\n";



template<class... Args>
inline void print(std::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    std::print(stdout, PRINT_PREFIX);
    std::print(stdout, fmt, std::forward<Args>(args)...);
    std::print(stdout, PRINT_POSTFIX);
}


template<class... Args>
inline void info(std::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    std::print(stdout, INFO_PREFIX);
    std::print(stdout, fmt, std::forward<Args>(args)...);
    std::print(stdout, INFO_POSTFIX);
}

template<class... Args>
inline void warning(std::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    std::print(stderr, WARNING_PREFIX);
    std::print(stderr, fmt, std::forward<Args>(args)...);
    std::print(stderr, WARNING_POSTFIX);
}

template<class... Args>
inline void error(std::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    std::print(stderr, ERROR_PREFIX);
    std::print(stderr, fmt, std::forward<Args>(args)...);
    std::print(stderr, ERROR_POSTFIX);
    fflush(stdout);
}

template<int32 ret=1, class... Args>
inline void fatal(std::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    std::print(stderr, "{}{}{}",
        FATAL_PREFIX, std::format(fmt, std::forward<Args>(args)...), FATAL_POSTFIX
    );
    ::exit(ret);
}


NAMESPACE_END(log)
NAMESPACE_END(vexa)
