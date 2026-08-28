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
    return math::sqrt(
        math::pow(CAST<fp32>(first.x-second.x), 2) +
        math::pow(CAST<fp32>(first.y-second.y), 2)
    );
}


struct Vec2 {
    using ValueT = fp32;
    ValueT x;
    ValueT y;

    constexpr Vec2(): x(ValueT{}), y(ValueT{}) {}
    constexpr Vec2(ValueT x, ValueT y): x(x), y(y) {}

    constexpr bool operator== (Vec2 other) const noexcept { return VecEqu(*this, other); }

    constexpr Vec2& operator+= (const Vec2& other) noexcept {
        *this = VecAdd(*this, other);  return *this;
    }
    constexpr Vec2& operator-= (const Vec2& other) noexcept {
        *this = VecSub(*this, other);  return *this;
    }

    constexpr Vec2 operator+ (const Vec2& other) const noexcept { return VecAdd(*this,other); }
    constexpr Vec2 operator- (const Vec2& other) const noexcept { return VecSub(*this,other); }
    constexpr ValueT operator, (const Vec2& other) const noexcept { return VecDist(*this,other); }

    constexpr ValueT dist(const Vec2& other) const noexcept { return (*this),other; }
};


struct Vec2i {
    using ValueT = int32;
    ValueT x;
    ValueT y;
    constexpr Vec2i(ValueT x, ValueT y): x(x), y(y) {}
    constexpr bool operator== (Vec2i other) const noexcept { return VecEqu(*this, other); }

    constexpr Vec2i& operator+= (const Vec2i& other) noexcept {
        *this = VecAdd(*this, other);  return *this;
    }
    constexpr Vec2i& operator-= (const Vec2i& other) noexcept {
        *this = VecSub(*this, other);  return *this;
    }

    constexpr Vec2i operator+ (const Vec2i& other) const noexcept { return VecAdd(*this,other); }
    constexpr Vec2i operator- (const Vec2i& other) const noexcept { return VecSub(*this,other); }
    constexpr ValueT operator, (const Vec2i& other) const noexcept { return VecDist(*this,other); }

    constexpr ValueT dist(const Vec2i& other) const noexcept { return (*this),other; }
};


struct Vec2u {
    using ValueT = uint32;
    ValueT x;
    ValueT y;
    constexpr Vec2u(ValueT x, ValueT y): x(x), y(y) {}
    constexpr bool operator== (Vec2u other) const noexcept { return VecEqu(*this, other); }

    constexpr Vec2u& operator+= (const Vec2u& other) noexcept {
        *this = VecAdd(*this, other);  return *this;
    }
    constexpr Vec2u& operator-= (const Vec2u& other) noexcept {
        *this = VecSub(*this, other);  return *this;
    }

    constexpr Vec2u operator+ (const Vec2u& other) const noexcept { return VecAdd(*this,other); }
    constexpr Vec2u operator- (const Vec2u& other) const noexcept { return VecSub(*this,other); }
    constexpr ValueT operator, (const Vec2u& other) const noexcept { return VecDist(*this,other); }

    constexpr ValueT dist(const Vec2u& other) const noexcept { return (*this),other; }
};


NAMESPACE_END(vec)
NAMESPACE_END(vexa)
