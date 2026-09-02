#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)

template<class EnumType>
inline constexpr usize enum_len = CAST<usize>(EnumType::COUNT);

inline constexpr usize cstrLen(const char8* cstr) noexcept {
    usize n = 0; while (*cstr++ != '\0') ++n;
    return n;
}

inline constexpr usize cstrLen(const char16* cstr) noexcept {
    usize n = 0; while (*cstr++ != '\0') ++n;
    return n;
}

inline constexpr usize cstrLen(const char32* cstr) noexcept {
    usize n = 0; while (*cstr++ != '\0') ++n;
    return n;
}


template<typename T, usize N>
inline consteval usize elemSize(const T (&array)[N]) noexcept {
    return sizeof(T);  (void)array;
}
// overload for containers with the underlying type that has ::value_type or ::ValueT
template<typename T> requires
( requires { typename T::ValueT; } ||
requires { typename T::value_type; } )
inline consteval usize elemSize(const T&) noexcept {
    if constexpr (requires { typename T::ValueT; }) return sizeof(typename T::ValueT);
    else return sizeof(typename T::value_type);
}


NAMESPACE_END(vexa)
