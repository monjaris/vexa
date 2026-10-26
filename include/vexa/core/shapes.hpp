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
    explicit constexpr inline Triangle(VecT pos1, VecT pos2, VecT pos3)
        : first(pos1), middle(pos2), last(pos3) {}


    fp32 side1() const {
        return VecDist(first, middle);
    }
    fp32 side2() const {
        return VecDist(middle, last);
    }
    fp32 side3() const {
        return VecDist(last, first);
    }

    constexpr fp32 area() const {
        fp32 semi_p = Perimeter(this->side1(), this->side2(), this->side3()) / 2.0f;
        return math::sqrt(semi_p*(semi_p-side1())*(semi_p-side2())*(semi_p-side3()));
    }
};




struct Rect {
    Vec2 pos;
    Vec2 size;


    // default ctor
    constexpr Rect(): pos({0, 0}), size({0, 0}) {}

    // create a rectangle: (x, y, w, h)
    constexpr inline Rect(
        Vec2::ValueT x, Vec2::ValueT y, Vec2::ValueT width, Vec2::ValueT height
    ): pos({x, y}), size(width, height) {}

    // create a rectangle: ({x, y}, {w, h})
    constexpr Rect(Vec2 position, Vec2 size)
        : pos(position), size(size) {}

    // create a square: ({x, y}, a)
    constexpr Rect(Vec2 position, Vec2::ValueT side)
        : pos(position), size({side, side}) {}


    // methods: empty(), area(), perimeter(), center()
    constexpr inline bool isEmpty()
        const { return !pos.x && !pos.y && !size.x && !size.y; }
    constexpr inline Vec2::ValueT area()
        const { return size.x * size.y; }
    constexpr inline Vec2::ValueT perimeter()
        const { return 2*(size.x + size.y); }
    constexpr inline Vec2 center()
        const { return {pos.x + size.x / 2, pos.y + size.y / 2}; }

    // methods: left(), right(), top(), bottom()
    constexpr inline Vec2 left()
    const { return {pos.x, pos.y + size.y / 2}; }
    constexpr inline Vec2 right()
    const { return {pos.x + size.x, pos.y + size.y / 2}; }
    constexpr inline Vec2 top() 
    const { return {pos.x + size.x / 2, pos.y}; }
    constexpr inline Vec2 bottom()
    const { return {pos.x + size.x / 2, pos.y + size.y}; }

    // methods: topLeft(), topRight(), bottomLeft(), bottomRight()
    constexpr inline Vec2 topLeft()
    const { return pos; }
    constexpr inline Vec2 topRight()
    const { return {pos.x + size.x, pos.y}; }
    constexpr inline Vec2 bottomLeft()
    const { return {pos.x,pos.y + size.y}; }
    constexpr inline Vec2 bottomRight()
    const { return {pos.x + size.x, pos.y + size.y}; }
};



struct VX_NODISCARD Circle {
    Vec2 pos;
    Vec2::ValueT radius;

    //  quality of the circle (scales segments)  //
    static constexpr fp32 POOR = 0.030;
    static constexpr fp32 FAIR = 0.060;
    static constexpr fp32 NORMAL = 0.100;
    static constexpr fp32 CRISP = 0.180;
    static constexpr fp32 PERFECT = 0.270;

    // create a circle: ({x, y}, r)
    explicit constexpr inline Circle(Vec2 position, Vec2::ValueT radius)
        : pos(position), radius(radius) {}


    constexpr Vec2::ValueT area() const {
        return math::PI32 * math::pow(radius, 2);
    }

    constexpr Vec2::ValueT circumference() const {
        return 2.f * math::PI32 * radius;
    }

    Circle& enlarge(const fp64 percent) {
        radius += radius * percent * 0.01f;
        return *this;
    }

    constexpr uint32 segments(fp32 quality) {
        return quality * (2.0f * math::PI32 * radius);
    }
};


NAMESPACE_END(shapes)
NAMESPACE_END(vexa)
