#pragma once


using nullptrT = decltype(nullptr);
using usize = __SIZE_TYPE__;
using isize = __PTRDIFF_TYPE__;

using char8 = char;
using char16 = char16_t;
using char32 = char32_t;

using fp32 = float;
using fp64 = double;

using int8  = __INT8_TYPE__;
using int16 = __INT16_TYPE__;
using int32 = __INT32_TYPE__;
using int64 = __INT64_TYPE__;

using uint8  = __UINT8_TYPE__;
using uint16 = __UINT16_TYPE__;
using uint32 = __UINT32_TYPE__;
using uint64 = __UINT64_TYPE__;



// check if T and U are same type
template<typename T, typename U> inline constexpr bool is_same_t = false;
template<typename T> inline constexpr bool is_same_t<T, T> = true;
template<class T, class U> concept same_as = is_same_t<T, U>;

// check if T and U are same type (variadic)
template<typename T, typename... U> inline constexpr bool is_any_same_t = (is_same_t<T, U> || ...);
template<typename T, typename... U>
concept any_same_as = is_any_same_t<T, U...>;


namespace typeimpl {
    template<class T> struct IsLvalReferenceImpl { constexpr static bool value = false; };
    template<class T> struct IsLvalReferenceImpl<T&> { constexpr static bool value = true; };
    template<class T> struct IsLvalReferenceImpl<T&&> { constexpr static bool value = false; };

    template<class T> struct IsRvalReferenceImpl { constexpr static bool value = false; };
    template<class T> struct IsRvalReferenceImpl<T&> { constexpr static bool value = false; };
    template<class T> struct IsRvalReferenceImpl<T&&> { constexpr static bool value = true; };

    template<class T> struct RemoveReferenceImpl { using Type = T; };
    template<class T> struct RemoveReferenceImpl<T&> { using Type = T; };
    template<class T> struct RemoveReferenceImpl<T&&> { using Type = T; };

    template<class T> struct RemoveConstImpl { using Type = T; };
    template<class T> struct RemoveConstImpl<const T> { using Type = T; };

    template<class T> struct NoDeduceImpl { using Type = T; };

    template<class T> struct UnderlyingTypeImpl { using Type = __underlying_type(T); };
}


template<class T>
using RmRef = typeimpl::RemoveReferenceImpl<T>::Type;

template<class T>
using RmConst = typeimpl::RemoveConstImpl<T>::Type;

template<class T>
constexpr bool is_lvref = typeimpl::IsLvalReferenceImpl<T>::value;

template<class T>
constexpr bool is_rvref = typeimpl::IsRvalReferenceImpl<T>::value;

template<class T>
using NoDeduce = typeimpl::NoDeduceImpl<T>::Type;


template<class T> using enum_t = typeimpl::UnderlyingTypeImpl<T>::Type;

template<class EnumType>
enum_t<EnumType> enum_v(EnumType enum_member) {
    return static_cast<enum_t<EnumType>>(enum_member);
}



template<typename CharT>
concept CharConcept = (
    is_any_same_t<CharT, char8, char16, char32, unsigned char, wchar_t>
);

template<typename IntT>
concept IntConcept = (
    is_any_same_t<IntT, int8, int16, int32, int64>
);

template<typename UintT>
concept UintConcept = (
    is_any_same_t<UintT, uint8, uint16, uint32, uint64>
);

template<typename FloatT>
concept FloatConcept = (
    is_any_same_t<FloatT, fp32, fp64>
);

