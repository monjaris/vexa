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


//  SQRT (consteval)  //
consteval auto sqrtCT(auto x) {
    using T = decltype(x);
    if (x < CAST(T, 0)) static_assert(true, "sqrt of negative number is undefined");
    IF_THEN(x == CAST(T, 0) || x != x,   return x;)  // x!=x can return true with NANs

    auto prev = CAST(T, 0);
    auto curr = (x < CAST(T, 1))?  CAST(T, 1) : x;

    while (curr != prev) {
        prev = curr;
        curr = static_cast<T>(0.5) * (curr + x / curr);
    }
    return curr;
}

//  SQRT  //
constexpr inline auto sqrt(fp32 x) -> decltype(x) {
    return std::sqrtf(x);
}
constexpr inline auto sqrt(fp64 x) -> decltype(x) {
    return std::sqrt(x);
}


//  POW  //
constexpr inline fp32 pow(fp32 x, fp32 exp) noexcept {
    return std::powf(x, exp);
}
constexpr inline fp64 pow(fp64 x, fp64 exp) noexcept {
    return std::pow(x, exp);
}



// convert radians to degrees
constexpr inline fp32 toDegrees(fp32 radians) noexcept {
    return radians * 180.0f * PI32_INV;
}
constexpr inline fp64 toDegrees(fp64 radians) noexcept {
    return radians * 180.0 * PI64_INV;
}
// convert degrees to radians
constexpr inline fp32 toRadians(fp32 degrees) noexcept {
    return degrees * (PI32 / 180.0f);
}
constexpr inline fp64 toRadians(fp64 degrees) noexcept {
    return degrees * (PI64 / 180.0);
}



//  Trigonometry  //
// sin
constexpr fp32 sin(fp32 rad) { return std::sinf(rad); }
constexpr fp64 sin(fp64 rad) { return std::sin(rad); }
constexpr fp32 sinDeg(fp32 deg) { return std::sinf(toRadians(deg)); }
constexpr fp64 sinDeg(fp64 deg) { return std::sin(toRadians(deg)); }
// cos
constexpr fp32 cos(fp32 rad) { return std::cosf(rad); }
constexpr fp64 cos(fp64 rad) { return std::cos(rad); }
constexpr fp32 cosDeg(fp32 deg) { return std::cosf(toRadians(deg)); }
constexpr fp64 cosDeg(fp64 deg) { return std::cos(toRadians(deg)); }
// tan
constexpr fp32 tan(fp32 rad) { return std::tanf(rad); }
constexpr fp64 tan(fp64 rad) { return std::tan(rad); }
constexpr fp32 tanDeg(fp32 deg) { return std::tanf(toRadians(deg)); }
constexpr fp64 tanDeg(fp64 deg) { return std::tan(toRadians(deg)); }
// cot
constexpr fp32 cot(fp32 rad) { return 1.0f / std::tanf(rad); }
constexpr fp64 cot(fp64 rad) { return 1.0 / std::tan(rad); }
constexpr fp32 cotDeg(fp32 deg) { return 1.0f / std::tanf(toRadians(deg)); }
constexpr fp64 cotDeg(fp64 deg) { return 1.0 / std::tan(toRadians(deg)); }


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
