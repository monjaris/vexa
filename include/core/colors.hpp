#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(colors)

// class declarations
template <typename T> requires (is_same_t<uint8, T> || is_same_t<fp32, T>) struct ColorBase;
struct ColorF32;  struct ColorU8;  // both derives from ColorBase template


template <typename T>
requires (is_same_t<uint8, T> || is_same_t<fp32, T>)
struct ColorBase {
    T r, g, b;
    T a = T{1};

    // increase r, g and b values by @arg n
    T& increase(T n) {
        r += n;
        g += n;
        b += n;
        return *this;
    }

    // decrease r, g and b values by @arg n
    T& decrease(T n) {
        r -= n;
        g -= n;
        b -= n;
        return *this;
    }
};



struct ColorU8 : ColorBase<uint8> {
    using This = ColorU8;
    using Value = uint8;

    constexpr ColorU8(
        Value r,
        Value g,
        Value b,
        Value a = 255
    ) : ColorBase<Value>{r, g, b, a}
    {}


    constexpr ColorF32 toF32() const noexcept;


    static const This BLACK;
    static const This WHITE;
    static const This GREY;
    //
    static const This RED;
    static const This GREEN;
    static const This BLUE;
    //
    static const This YELLOW;
    static const This CYAN;
    static const This MAGENTA;
};


struct ColorF32 : ColorBase<fp32> {
    using This = ColorF32;
    using Value = fp32;

    constexpr ColorF32(
        Value r,
        Value g,
        Value b,
        Value a = 1.0f
    ) : ColorBase<Value>{r, g, b, a}
    {}


    constexpr ColorU8 toU8() const noexcept;


    static const This BLACK;
    static const This WHITE;
    static const This GREY;
    //
    static const This RED;
    static const This GREEN;
    static const This BLUE;
    //
    static const This YELLOW;
    static const This CYAN;
    static const This MAGENTA;
};


template<class T>
concept ColorConcept = (
    is_same_t<ColorU8, T> || is_same_t<ColorF32, T>
);



constexpr ColorF32 ColorU8::toF32() const noexcept {
    constexpr fp32 scale = 1.0f / 255.0f;

    return { r * scale,  g * scale,  b * scale,  a * scale };
}


constexpr ColorU8 ColorF32::toU8() const noexcept {
    constexpr fp32 scale = 255.0f;

    return {
        static_cast<ColorU8::Value>(r * scale), static_cast<ColorU8::Value>(g * scale),
        static_cast<ColorU8::Value>(b * scale), static_cast<ColorU8::Value>(a * scale)
    };
}



constexpr inline const ColorU8 ColorU8::BLACK   = {0, 0, 0};
constexpr inline const ColorU8 ColorU8::WHITE   = {255, 255, 255};
constexpr inline const ColorU8 ColorU8::GREY    = {128, 128, 128};
constexpr inline const ColorU8 ColorU8::RED     = {255, 0, 0};
constexpr inline const ColorU8 ColorU8::GREEN   = {0, 255, 0};
constexpr inline const ColorU8 ColorU8::BLUE    = {0, 0, 255};
constexpr inline const ColorU8 ColorU8::YELLOW  = {255, 255, 0};
constexpr inline const ColorU8 ColorU8::CYAN    = {0, 255, 255};
constexpr inline const ColorU8 ColorU8::MAGENTA = {255, 0, 255};


constexpr inline const ColorF32 ColorF32::BLACK   = {0.0f, 0.0f, 0.0f};
constexpr inline const ColorF32 ColorF32::WHITE   = {1.0f, 1.0f, 1.0f};
constexpr inline const ColorF32 ColorF32::GREY    = {0.5f, 0.5f, 0.5f};
constexpr inline const ColorF32 ColorF32::RED     = {1.0f, 0.0f, 0.0f};
constexpr inline const ColorF32 ColorF32::GREEN   = {0.0f, 1.0f, 0.0f};
constexpr inline const ColorF32 ColorF32::BLUE    = {0.0f, 0.0f, 1.0f};
constexpr inline const ColorF32 ColorF32::YELLOW  = {1.0f, 1.0f, 0.0f};
constexpr inline const ColorF32 ColorF32::CYAN    = {0.0f, 1.0f, 1.0f};
constexpr inline const ColorF32 ColorF32::MAGENTA = {1.0f, 0.0f, 1.0f};



NAMESPACE_END(colors)
NAMESPACE_END(vexa)
