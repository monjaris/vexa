#pragma once

#define VX_VERSION "v0.2.0"

namespace vexa {
    inline namespace types {
        #include "types.hpp"
    }
}



#define NAMESPACE_BEGIN($NAME) namespace $NAME {
#define NAMESPACE_END($NS_NAME_OPTIN) }
#define CAST static_cast
#define PANIC() __builtin_trap()

#define IF_THEN($CONDITION, $STATEMENT) if(($CONDITION)) {DEFINE_STMT($STATEMENT)}
#define CASE_OR($CASE_1, $CASE_2)  case $CASE_1: case $CASE_2

// throw error at compile time - only should be used inside `consteval` functions
#define CASSERT($COND, $MESSAGE) { if(!($COND)) vx_force_compile_time_error($MESSAGE); }
consteval void vx_force_compile_time_error(const char*) {}



#if defined(_WIN32)
extern "C" int _write(int, const void*, unsigned int);
#define VX_WRITE ::_write
#else
extern "C" long write(int, const void*, unsigned long);
#define VX_WRITE ::write
#endif


#define TODO_IMPL "Unimplemented: "

#define TODO($WHAT) do { \
        static constexpr char _todo_msg[] = $WHAT; \
        static constexpr char _todo_prefix[] = "\033[34m[TODO]\033[0m "; \
        static constexpr char _file_name[] = "\033[4m" __FILE__ "\033[0m"; \
        static constexpr char _line[] = ":\033[1m" VX_LINE_STR "\033[0m"; \
        static constexpr char _nl = '\n'; \
        VX_WRITE(2, _todo_prefix, sizeof(_todo_prefix) - 1); \
        VX_WRITE(2, _todo_msg, sizeof(_todo_msg) - 1); \
        VX_WRITE(2, _file_name, sizeof(_file_name) - 1); \
        VX_WRITE(2, _line, sizeof(_line) - 1); \
        VX_WRITE(2, &_nl, 1); \
        PANIC(); \
    } while (0);


#define DO_PRAGMA($PRAGMA) _Pragma(#$PRAGMA)
#define DEFINE_STMT($STATEMENT) do {$STATEMENT} while(false);

#define IGNORE_WARNING_BEGIN($DIAGNOSTIC) \
    DO_PRAGMA(GCC diagnostic push) \
    DO_PRAGMA(GCC diagnostic ignored $DIAGNOSTIC)

#define IGNORE_WARNING_END($DIAGNOSTIC_OPTIN) \
    DO_PRAGMA(GCC diagnostic pop)


#define VX_STRINGIFY_IMPL(x) #x
#define VX_STRINGIFY(x) VX_STRINGIFY_IMPL(x)
#define VX_LINE_STR VX_STRINGIFY(__LINE__)


#define GEN_BITOPS($TYPE, $UNDERLYING) \
    constexpr $TYPE operator~ ($TYPE right) noexcept { \
        return CAST<$TYPE>(~CAST<$UNDERLYING>(right)); \
    } \
    constexpr $TYPE operator& ($TYPE left, $TYPE right) noexcept { \
        return static_cast<$TYPE>(CAST<$UNDERLYING>(left) & CAST<$UNDERLYING>(right)); \
    } \
    \
    constexpr $TYPE operator| ($TYPE left, $TYPE right) noexcept { \
        return static_cast<$TYPE>(CAST<$UNDERLYING>(left) | CAST<$UNDERLYING>(right)); \
    } \
    \
    constexpr $TYPE& operator&= ($TYPE& left, const $TYPE& right) noexcept { \
        return (left = left & right); \
    } \
    \
    constexpr $TYPE& operator|= ($TYPE& left, const $TYPE& right) noexcept { \
        return (left = left | right); \
    } \



#define VX_MAP($VEXA, $SDL) case $SDL: return $VEXA; break
#define VX_REVERSE_MAP($SDL, $VEXA) case $VEXA: return $SDL; break

#define VX_NODISCARD  [[nodiscard]]

#define LAUNDER($PTR) __builtin_launder($PTR);

#define VX_STATIC_ERR($MESSAGE) static_assert(false, $MESSAGE)


#define VX_STATIC_CLASS : private CN_SC
class CN_SC {
    // delete ctor/dtor
    CN_SC() = delete;  ~CN_SC() = delete;
    // delete copy ops
    CN_SC(const CN_SC&) = delete;  CN_SC& operator=(const CN_SC&) = delete;
    // delete move ops
    CN_SC(CN_SC&&) = delete;  CN_SC& operator=(CN_SC&&) = delete;
};

#define VX_UNREACHABLE() __builtin_unreachable()

#define VX_UNUSE(...)  (unuse_symbol(__VA_ARGS__));
namespace vexa { template<typename... Args> constexpr void unuse_symbol(Args&&...) noexcept {} }
