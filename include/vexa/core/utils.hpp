#pragma once
#include "defs.hpp"
#include <type_traits>
NAMESPACE_BEGIN(vexa)

template<class EnumType>
inline constexpr usize enum_len = CAST<usize>(EnumType::COUNT);

VX_NODISCARD constexpr usize cstrLen(const char8* cstr) noexcept {
    usize n = 0; while (*cstr++ != '\0') ++n;
    return n;
}

VX_NODISCARD constexpr usize cstrLen(const char16* cstr) noexcept {
    usize n = 0; while (*cstr++ != '\0') ++n;
    return n;
}

VX_NODISCARD constexpr usize cstrLen(const char32* cstr) noexcept {
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




constexpr bool isCstrEqu(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) return false;

    usize str1_len = cstrLen(str1);
    usize str2_len = cstrLen(str2);
    if (str1_len != str2_len) return false;

    for (usize i=0;  i < str1_len;  ++i) {
        if (str1[i] != str2[i]) return false;
    }

    return true;
}



NAMESPACE_END(vexa)
