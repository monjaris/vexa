#pragma once
#include "defs.hpp"
#include "math.hpp"
NAMESPACE_BEGIN(vexa)

struct Angle {
    fp32 radians;

    constexpr Angle (fp32 radians): radians(radians) {}
    constexpr Angle (fp32 degrees, void* null): radians(math::toRadians(degrees)) {}

    // returns angle value in degrees
    constexpr fp32 degrees() const {
        return math::toDegrees(radians);
    }

    constexpr fp32 clamp() {
        return math::clamp(radians, 0.f, 360.f);
    }

    constexpr fp32 normalize() const {
        return Angle{radians}.clamp() * (1.f/math::PI32);
    }
};


NAMESPACE_END(vexa)
