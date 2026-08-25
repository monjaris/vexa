#pragma once
#include <cmath>
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(math)

// compile time PI as fp32 and fp64
constexpr fp32 PI32 = 3.14159265f;
constexpr fp64 PI64 = 3.14159265358979323846;
// to make (x / PI32) and (x / PI64) optimizable, where x is a runtime value
constexpr fp32 PI32_INV = 1.0f/3.14159265f;
constexpr fp64 PI64_INV = 1.0f/3.14159265358979323846;


// consteval sqrt for fp32
template <const fp32 x>
consteval inline auto sqrt_fp32_CT() -> decltype(x) {
    return std::sqrtf(x);
}
// consteval sqrt for fp64
template <const fp64 x>
consteval inline auto sqrt_fp64_CT() -> decltype(x) {
    return std::sqrt(x);
}
// sqrt for fp32
template <const fp32 x>
constexpr inline auto sqrt_fp32() -> decltype(x) {
    return std::sqrtf(x);
}
// sqrt for fp64
template <const fp64 x>
constexpr inline auto sqrt_fp64() -> decltype(x) {
    return std::sqrt(x);
}
// generic sqrt for metaprogramming
template<typename FloatT>
constexpr inline auto sqrt(FloatT x) {
    if constexpr (is_same_t<fp32, FloatT>) return std::sqrtf(x);
    else if constexpr (is_same_t<fp64, FloatT>) return std::sqrt(x);
    else static_assert(true, "invalid type");
}


// sqrt for fp32
constexpr inline fp32 pow(fp32 x, fp32 exp) noexcept {
    return std::powf(x, exp);
}
// pow for fp64
constexpr inline fp64 pow(fp64 x, fp64 exp) noexcept {
    return std::pow(x, exp);
}



// convert radians to degrees
constexpr fp32 toDegrees(fp32 radians) noexcept {
    return radians * 180.f * PI32_INV;
}
// convert degrees to radians
constexpr fp32 toRadians(fp32 degrees) noexcept {
    return degrees * (PI32 / 180.f);
}



// return clamped value of @arg value between @arg min and @arg max
template<class V>
constexpr V clamp(V value, V min, V max) {
    if (max < value) return max;
    else if (min > value) return min;
    return value;
}
// overload math::clamp for the case that 
template<class V, class T, class U>
constexpr auto clamp(V value, T min, U max) -> std::common_type_t<V, T, U> {
    if (max < value) return max;
    else if (min > value) return min;
    return value;
}


NAMESPACE_END(math)
NAMESPACE_END(vexa)
