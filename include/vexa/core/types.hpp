#pragma once

using usize = decltype(sizeof(nullptr));
using isize = decltype((char*)0 - (char*)0);

using char8 = char;
using int8 = char8;
using uint8 = unsigned char;

using char16 = char16_t;
using int16 = short;
using uint16 = unsigned short;

using char32 = char32_t;

using fp32 = float;
using fp64 = double;


#if __SIZEOF_SHORT__ == 4
    using int32 = short;
    using uint32 = unsigned short;
#elif __SIZEOF_INT__ == 4
    using int32 = int;
    using uint32 = unsigned int;
#elif __SIZEOF_LONG__ == 4
    using int32 = long;
    using uint32 = unsigned long;
#else
    #error No 4-byte integer type available!
#endif


#if __SIZEOF_INT__ == 8
    using int64 = int;
    using uint64 = unsigned int;
#elif __SIZEOF_LONG__ == 8
    using int64 = long;
    using uint64 = unsigned long;
#elif __SIZEOF_LONG_LONG__ == 8
    using int64 = long long;
    using uint64 = unsigned long long;
#else
    #error No 8-byte integer type available!
#endif


static_assert(sizeof(char8) == 1, "char8 must be 1 byte");
static_assert(sizeof(int8) == 1, "int8 must be 1 byte");
static_assert(sizeof(uint8) == 1, "uint8 must be 1 byte");

static_assert(sizeof(char16) == 2, "char16 must be 2 bytes");
static_assert(sizeof(int16) == 2, "int16 must be 2 bytes");
static_assert(sizeof(uint16) == 2, "uint16 must be 2 bytes");

static_assert(sizeof(char32) == 4, "char32 must be 4 bytes");
static_assert(sizeof(int32) == 4, "int32 must be 4 bytes");
static_assert(sizeof(uint32) == 4, "uint32 must be 4 bytes");
static_assert(sizeof(fp32) == 4, "fp32 must be 4 bytes");

static_assert(sizeof(int64) == 8, "int64 must be 8 bytes");
static_assert(sizeof(uint64) == 8, "uint64 must be 8 bytes");
static_assert(sizeof(fp64) == 8, "fp64 must be 8 bytes");



// check if T and U are same type
template<typename T, typename U> inline constexpr bool is_same_t = false;
template<typename T> inline constexpr bool is_same_t<T, T> = true;
template<class T, class U> concept is_same_as = is_same_t<T, U>;

// check if T and U are same type (variadic)
template<typename T, typename... U> inline constexpr bool is_any_same_t = (is_same_t<T, U> || ...);
template<typename T, typename... U>
concept is_any_same_as = is_any_same_t<T, U...>;


// get underlying type via cross-compiler instrinct
template<class T> using enum_t = __underlying_type(T);
// get integral value of an enum(class) member
template<class EnumType>
auto enum_v(EnumType enum_member) -> enum_t<EnumType> {
    return static_cast<enum_t<EnumType>>(enum_member);
}
