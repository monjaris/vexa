#pragma once
#include "vexa/alt/memory.hpp"
#include "vexa/core/common.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Renderer
{
    // friend needs to access this->impl
    friend class Window;
    class Impl;
    std::unique_ptr<Impl> impl;

    class VX_NODISCARD M_Cfg
    {
        friend class Renderer;
        friend class Window;
        CfgVal<bool> vsync;

    public:
        constexpr M_Cfg () noexcept:
            vsync(false)
        {}

        void reset() noexcept {
            vsync = vsync.defaultVal();
        }
    }
    m_build_config;


public:
    using Cfg = M_Cfg;

    Renderer(Cfg config = Cfg{});
    // rule of 5
    ~Renderer();
    Renderer(Renderer&& other) noexcept;
    Renderer& operator= (Renderer&& other) noexcept;
    Renderer (const Renderer& copy_ctor) = delete;
    Renderer& operator= (const Renderer& copy_operator) = delete;

    Renderer create(void* window_ptr);
    void destroy();
    bool exists();

    Renderer& setVsync(bool enabled = true);
    bool getVsync();

    void start();
    void start(ColorU8 color);
    void start(ColorF32 color);
    void finish();
    // void clear(ColorU8 color);

    void triangleFill(Triangle triangle, ColorU8 color);
    void triangleFill(Triangle triangle, ColorF32 color);
    void triangleLines(Triangle triangle, ColorU8 color);
    void triangleLines(Triangle triangle, ColorF32 color);
    template<usize N> void triangleFillN(Triangle (&triangle_array)[N], ColorU8 color);
    template<usize N> void triangleFillN(Triangle (&triangle_array)[N], ColorF32 color);
    template<usize N> void triangleLinesN(Triangle (&triangle_array)[N], ColorU8 color);
    template<usize N> void triangleLinesN(Triangle (&triangle_array)[N], ColorF32 color);
    //
    void rectFill(Rect rectangle, ColorU8 color);
    void rectFill(Rect rectangle, ColorF32 color);
    void rectLines(Rect rectangle, ColorU8 color);
    void rectLines(Rect rectangle, ColorF32 color);
    template<usize N> void rectFillN(Rect (&rectangle_array)[N], ColorU8 color);
    template<usize N> void rectFillN(Rect (&rectangle_array)[N], ColorF32 color);
    template<usize N> void rectLinesN(Rect (&rectangle_array)[N], ColorU8 color);
    template<usize N> void rectLinesN(Rect (&rectangle_array)[N], ColorF32 color);
    //
    void PolyFill(Vec2 pos, Vec2 size, ColorU8 color);
    void PolyLines(Vec2 pos, Vec2 size, ColorU8 color);
    //
    void circleFill(Circle circle, ColorF32 color, fp32 quality = Circle::NORMAL);
    void circleFill(Circle circle, ColorU8 color, fp32 quality = Circle::NORMAL);
    void circleLines(Circle circle, ColorU8 color);
    void circleLines(Circle circle, ColorF32 color);
};

NAMESPACE_END(vexa)
