#pragma once
#include <array>
#include "defs.hpp"
#include "vec.hpp"
#include "math.hpp"
// forward declare cmath functions
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(shapes)


// returns sum of all sides
template<typename... Sides>
constexpr inline fp32 Perimeter(const Sides&&... sides) {
    return (sides + ...);
}
// consteval version of shapes::Perimeter() for guaranteed compile-time execution
template<typename... Sides>
consteval inline fp32 PerimeterCT(const Sides... sides) {
    return (sides + ...);
}




struct Triangle {
    using VecT = Vec2f;
    VecT first;
    VecT middle;
    VecT last;

    // create a triangle: (pos1, pos2, pos3)
    explicit constexpr inline Triangle(VecT pos1, VecT pos2, VecT pos3) noexcept
        : first(pos1), middle(pos2), last(pos3) {}


    fp32 side1() const noexcept {
        return VecDist(first, middle);
    }
    fp32 side2() const noexcept {
        return VecDist(middle, last);
    }
    fp32 side3() const noexcept {
        return VecDist(last, first);
    }

    constexpr fp32 area() const noexcept {
        fp32 semi_p = Perimeter(this->side1(), this->side2(), this->side3()) / 2.0f;
        return math::sqrt(semi_p*(semi_p-side1())*(semi_p-side2())*(semi_p-side3()));
    }
};




struct Rect {
    Vec2f pos;
    Vec2f size;

    // create a rectangle: (x, y, w, h)
    explicit constexpr inline Rect(
        Vec2f::ValueT x, Vec2f::ValueT y, Vec2f::ValueT width, Vec2f::ValueT height
    ) noexcept: pos({x, y}), size(width, height) {}

    // create a rectangle: ({x, y}, {w, h})
    constexpr inline Rect(Vec2f position, Vec2f size) noexcept
        : pos(position), size(size) {}

    // create a square: ({x, y}, a)
    constexpr inline Rect(Vec2f position, Vec2f::ValueT side) noexcept
        : pos(position), size({side, side}) {}


    // methods: area(), perimeter(), center()
    constexpr inline Vec2f::ValueT area()
    const noexcept { return size.x * size.y; }
    constexpr inline Vec2f::ValueT perimeter()
    const noexcept { return 2*(size.x + size.y); }
    constexpr inline Vec2f center()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y / 2}; }

    // methods: left(), right(), top(), bottom()
    constexpr inline Vec2f left()
    const noexcept { return {pos.x, pos.y + size.y / 2}; }
    constexpr inline Vec2f right()
    const noexcept { return {pos.x + size.x, pos.y + size.y / 2}; }
    constexpr inline Vec2f top() 
    const noexcept { return {pos.x + size.x / 2, pos.y}; }
    constexpr inline Vec2f bottom()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y}; }

    // methods: topLeft(), topRight(), bottomLeft(), bottomRight()
    constexpr inline Vec2f topLeft()
    const noexcept { return pos; }
    constexpr inline Vec2f topRight()
    const noexcept { return {pos.x + size.x, pos.y}; }
    constexpr inline Vec2f bottomLeft()
    const noexcept { return {pos.x,pos.y + size.y}; }
    constexpr inline Vec2f bottomRight()
    const noexcept { return {pos.x + size.x, pos.y + size.y}; }
};




constexpr uint32 SEGMENTS = 1000;
template<uint32 t_segments = SEGMENTS>
struct Circle {
    Vec2f pos;
    Vec2f::ValueT radius;

    // create a circle: ({x, y}, r)
    explicit constexpr inline Circle(Vec2f position, Vec2f::ValueT radius) noexcept
        : pos(position), radius(radius) {}


    constexpr Vec2f::ValueT area() const noexcept {
        return math::PI32 * math::pow(radius, 2);
    }

    constexpr Vec2f::ValueT perimeter() const noexcept {
        return 2.f * math::PI32 * radius;
    }

    constexpr auto segments() const noexcept -> decltype(t_segments) {
        return t_segments;
    }

    Circle& enlarge(const fp64 percent) noexcept {
        radius += radius * percent * 0.01f;
        return *this;
    }
};


NAMESPACE_END(shapes)
NAMESPACE_END(vexa)
