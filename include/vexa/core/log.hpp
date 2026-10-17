#pragma once
#include <cstdlib>
#include <string>
#include <utility>
#include "vexa/alt/tiny-fmt.hpp"
#include "defs.hpp"
#include "memory.hpp"

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
inline void print(tfmt::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    tfmt::print(stdout, PRINT_PREFIX);
    tfmt::print(stdout, fmt, mem::forward<Args>(args)...);
    tfmt::print(stdout, PRINT_POSTFIX);
}


template<class... Args>
inline void info(tfmt::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    tfmt::print(stdout, INFO_PREFIX);
    tfmt::print(stdout, fmt, mem::forward<Args>(args)...);
    tfmt::print(stdout, INFO_POSTFIX);
}


template<class... Args>
inline void warning(tfmt::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    tfmt::print(stderr, WARNING_PREFIX);
    tfmt::print(stderr, fmt, mem::forward<Args>(args)...);
    tfmt::print(stderr, WARNING_POSTFIX);
}

template<class... Args>
inline void error(tfmt::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    tfmt::print(stderr, ERROR_PREFIX);
    tfmt::print(stderr, fmt, mem::forward<Args>(args)...);
    tfmt::print(stderr, ERROR_POSTFIX);
    fflush(stdout);
}

template<int32 ret=1, class... Args>
inline void fatal(tfmt::format_string<Args...> fmt, Args&&... args) {
    if (!intern::logging_enabled) return;
    tfmt::print(stderr, "{}{}{}",
        FATAL_PREFIX, tfmt::format(fmt, mem::forward<Args>(args)...), FATAL_POSTFIX
    );
    ::exit(ret);
}


NAMESPACE_END(log)
NAMESPACE_END(vexa)
