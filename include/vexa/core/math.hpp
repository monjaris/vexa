#pragma once
#include <cmath>
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(math)


//  SQRT (consteval)  //
template<uint8 iterations = 64>
consteval auto sqrtCT(auto x) {
    using T = decltype(x);

    if(x < CAST<T>(0)) {
        VX_WRITE(2, "sqrt of negative number is undefined\n", 38);
    }

    // is 0 or NAN
    if (x == T{0} || x != x) {
        return x;
    }

    T curr = (x < T{1})? (T{1}):(x);
    for (uint8 i=0;  i < iterations;  ++i) {
        curr = (curr + x / curr) * 0.5;
    }
    return curr;
}

//  SQRT  //
constexpr inline auto sqrt(fp32 x) -> decltype(x) {
    return ::sqrtf(x);
}
constexpr inline auto sqrt(fp64 x) -> decltype(x) {
    return ::sqrt(x);
}


//  POW  //
constexpr inline fp32 pow(fp32 x, fp32 exp) {
    return ::powf(x, exp);
}
constexpr inline fp64 pow(fp64 x, fp64 exp) {
    return ::pow(x, exp);
}





inline NAMESPACE_BEGIN(constants)

// compile time PI as fp32 and fp64
constexpr fp32 PI32 = 3.14159265f;
constexpr fp64 PI64 = 3.14159265358979323846;
// to make (x / PI32) and (x / PI64) optimizable, where x is a runtime value
constexpr fp32 PI32_INV = 1.0f/3.14159265f;
constexpr fp64 PI64_INV = 1.0f/3.14159265358979323846;

constexpr fp32 SQRT2 = sqrtCT(2);
constexpr fp32 SQRT2_INV = 1.0f / SQRT2;

NAMESPACE_END(constants)





// convert radians to degrees
constexpr inline fp32 toDegrees(fp32 radians) {
    return radians * 180.0f * PI32_INV;
}
constexpr inline fp64 toDegrees(fp64 radians) {
    return radians * 180.0 * PI64_INV;
}
// convert degrees to radians
constexpr inline fp32 toRadians(fp32 degrees) {
    return degrees * (PI32 / 180.0f);
}
constexpr inline fp64 toRadians(fp64 degrees) {
    return degrees * (PI64 / 180.0);
}



//  Trigonometry  //
// sin
constexpr fp32 sin(fp32 rad) { return ::sinf(rad); }
constexpr fp64 sin(fp64 rad) { return ::sin(rad); }
constexpr fp32 sinDeg(fp32 deg) { return ::sinf(toRadians(deg)); }
constexpr fp64 sinDeg(fp64 deg) { return ::sin(toRadians(deg)); }
// cos
constexpr fp32 cos(fp32 rad) { return ::cosf(rad); }
constexpr fp64 cos(fp64 rad) { return ::cos(rad); }
constexpr fp32 cosDeg(fp32 deg) { return ::cosf(toRadians(deg)); }
constexpr fp64 cosDeg(fp64 deg) { return ::cos(toRadians(deg)); }
// tan
constexpr fp32 tan(fp32 rad) { return ::tanf(rad); }
constexpr fp64 tan(fp64 rad) { return ::tan(rad); }
constexpr fp32 tanDeg(fp32 deg) { return ::tanf(toRadians(deg)); }
constexpr fp64 tanDeg(fp64 deg) { return ::tan(toRadians(deg)); }
// cot
constexpr fp32 cot(fp32 rad) { return 1.0f / ::tanf(rad); }
constexpr fp64 cot(fp64 rad) { return 1.0 / ::tan(rad); }
constexpr fp32 cotDeg(fp32 deg) { return 1.0f / ::tanf(toRadians(deg)); }
constexpr fp64 cotDeg(fp64 deg) { return 1.0 / ::tan(toRadians(deg)); }


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
