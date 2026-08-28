#pragma once
#include "defs.hpp"
#include "vec.hpp"
#include "math.hpp"
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
    using VecT = Vec2;
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
    Vec2 pos;
    Vec2 size;


    // default ctor
    constexpr Rect() noexcept: pos({0, 0}), size({0, 0}) {}

    // create a rectangle: (x, y, w, h)
    explicit constexpr inline Rect(
        Vec2::ValueT x, Vec2::ValueT y, Vec2::ValueT width, Vec2::ValueT height
    ) noexcept: pos({x, y}), size(width, height) {}

    // create a rectangle: ({x, y}, {w, h})
    constexpr Rect(Vec2 position, Vec2 size) noexcept
        : pos(position), size(size) {}

    // create a square: ({x, y}, a)
    constexpr Rect(Vec2 position, Vec2::ValueT side) noexcept
        : pos(position), size({side, side}) {}


    // methods: area(), perimeter(), center()
    constexpr inline Vec2::ValueT area()
    const noexcept { return size.x * size.y; }
    constexpr inline Vec2::ValueT perimeter()
    const noexcept { return 2*(size.x + size.y); }
    constexpr inline Vec2 center()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y / 2}; }

    // methods: left(), right(), top(), bottom()
    constexpr inline Vec2 left()
    const noexcept { return {pos.x, pos.y + size.y / 2}; }
    constexpr inline Vec2 right()
    const noexcept { return {pos.x + size.x, pos.y + size.y / 2}; }
    constexpr inline Vec2 top() 
    const noexcept { return {pos.x + size.x / 2, pos.y}; }
    constexpr inline Vec2 bottom()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y}; }

    // methods: topLeft(), topRight(), bottomLeft(), bottomRight()
    constexpr inline Vec2 topLeft()
    const noexcept { return pos; }
    constexpr inline Vec2 topRight()
    const noexcept { return {pos.x + size.x, pos.y}; }
    constexpr inline Vec2 bottomLeft()
    const noexcept { return {pos.x,pos.y + size.y}; }
    constexpr inline Vec2 bottomRight()
    const noexcept { return {pos.x + size.x, pos.y + size.y}; }
};




struct VX_NODISCARD Circle {
    Vec2 pos;
    Vec2::ValueT radius;

    //  quality of the circle (scales segments)  //
    static constexpr fp32 POOR = 0.03;
    static constexpr fp32 FAIR = 0.06;
    static constexpr fp32 NORMAL = 0.125;
    static constexpr fp32 CRISP = 0.18;
    static constexpr fp32 PERFECT = 0.27;

    // create a circle: ({x, y}, r)
    explicit constexpr inline Circle(Vec2 position, Vec2::ValueT radius) noexcept
        : pos(position), radius(radius) {}


    constexpr Vec2::ValueT area() const noexcept {
        return math::PI32 * math::pow(radius, 2);
    }

    constexpr Vec2::ValueT circumference() const noexcept {
        return 2.f * math::PI32 * radius;
    }

    Circle& enlarge(const fp64 percent) noexcept {
        radius += radius * percent * 0.01f;
        return *this;
    }

    constexpr uint32 segments(fp32 quality) {
        return quality * (2.0f * math::PI32 * radius);
    }
};


NAMESPACE_END(shapes)
NAMESPACE_END(vexa)
