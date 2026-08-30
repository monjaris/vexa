#pragma once

namespace vexa {
    #include "types.hpp"
}

#define NAMESPACE_BEGIN($NAME) namespace $NAME {
#define NAMESPACE_END($NS_NAME_OPTIN) }
#define CAST static_cast
#define TODO($MESSAGE) auto _vexa_todo = $MESSAGE
#define IF_THEN($CONDITION, $STATEMENT) if(($CONDITION)) {DEFINE_STMT($STATEMENT)}
#define CASE_OR($CASE_1, $CASE_2)  case $CASE_1: case $CASE_2

// throw error at compile time - only should be used inside `consteval` functions
#define CASSERT($COND, $MESSAGE) { if(!($COND)) vx_force_compile_time_error($MESSAGE); }
consteval void vx_force_compile_time_error(const char*) {}

// #define DEBUG_LN() (void)(vexa::log::debug("{}:{} -> {}()", __FILE__, __LINE__, __func__), "")
// #define DEBUG_FUNC_MODE __func__
// #define DEBUG_FUNC_TEMPLATE($MODE) DEFINE_STMT(vexa::log::debug("{}()", $MODE);)
// #define DEBUG_FUNC() DEBUG_FUNC_TEMPLATE(DEBUG_FUNC_MODE)


#define DO_PRAGMA($PRAGMA) _Pragma(#$PRAGMA)
#define DEFINE_STMT($STATEMENT) do {$STATEMENT} while(false);

#define IGNORE_WARNING_BEGIN($DIAGNOSTIC) \
    DO_PRAGMA(GCC diagnostic push) \
    DO_PRAGMA(GCC diagnostic ignored $DIAGNOSTIC)

#define IGNORE_WARNING_END($DIAGNOSTIC_OPTIN) \
    DO_PRAGMA(GCC diagnostic pop)



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



#define VX_NODISCARD  [[nodiscard]]

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

#define VX_UNUSE(...)  (unuse_symbol(__VA_ARGS__));
namespace vexa { template<typename... Args> constexpr void unuse_symbol(Args&&...) noexcept {} }
