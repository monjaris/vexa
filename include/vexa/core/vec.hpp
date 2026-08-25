#pragma once
#include <concepts>
#include "defs.hpp"
#include "math.hpp"
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(vec)


template<class T>
concept VectorConcept = requires(T t) { t.x, t.y; };

template<VectorConcept VectorT>
static constexpr inline bool VecEqu(const VectorT& left, const VectorT& right) noexcept {
    return (left.x == right.x) && (left.y == right.y);
}

template<VectorConcept VectorT>
static constexpr inline VectorT VecAdd(const VectorT& left, const VectorT& right) noexcept {
    return {left.x + right.x, left.y + right.y};
}

template<VectorConcept VectorT>
static constexpr inline VectorT VecSub(const VectorT& left, const VectorT& right) noexcept {
    return {left.x + right.x, left.y + right.y};
}


// return distance between two points
template<VectorConcept VectorT>
constexpr VectorT::ValueT VecDist(const VectorT& first, const VectorT& second) {
    return math::sqrt(math::pow(first.x-second.x, 2) + math::pow(first.y-second.y, 2));
}


struct Vec2i {
    using ValueT = int32;
    ValueT x;
    ValueT y;
    constexpr Vec2i(ValueT x, ValueT y): x(x), y(y) {}
    constexpr bool operator== (Vec2i other) const noexcept { return VecEqu(*this, other); }
};

struct Vec2u {
    using ValueT = uint32;
    ValueT x;
    ValueT y;
    constexpr Vec2u(ValueT x, ValueT y): x(x), y(y) {}
    constexpr bool operator== (Vec2u other) const noexcept { return VecEqu(*this, other); }
};

struct Vec2f {
    using ValueT = fp32;
    ValueT x;
    ValueT y;
    constexpr Vec2f(ValueT x, ValueT y): x(x), y(y) {}
    constexpr bool operator== (Vec2f other) const noexcept { return VecEqu(*this, other); }
};


using Vec2 = Vec2f;


NAMESPACE_END(vec)
NAMESPACE_END(vexa)
