#pragma once
#include "alt/memory.hpp"
#include "core/common.hpp"
NAMESPACE_BEGIN(cone)


class CN_NODISCARD Renderer
{
    // friend needs to access this->impl
    friend class Window;
    class Impl;
    std::unique_ptr<Impl> impl;

    class CN_NODISCARD M_Cfg
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

        M_Cfg& operator= (const M_Cfg& other) noexcept = default;
    }
    m_build_config;


    // private methods
    constexpr bool _setColorU8(ColorU8 color);
    constexpr bool _setColorF32(ColorF32 color);

    inline void _line(Vec2f pos1, Vec2f pos2);
    inline void _line(Vec2f pos1, Vec2f pos2, uint32 thickness);
    inline void _line(Vec2f pos1, Vec2f pos2, uint32 thickness, int);

    inline void _triangleFill(Triangle triangle, ColorF32 color);
    inline void _triangleLines(Triangle triangle, ColorF32 color);
    template<usize N> inline void _triangleFillN(Triangle (&triangle_array)[N], ColorF32 color);
    template<usize N> inline void _triangleLinesN(Triangle (&triangle_array)[N], ColorF32 color);
    inline void _rectFill(Rect<> rectangle);
    inline void _rectLines(Rect<> rectangle);
    template<usize N> inline void _rectFillN(Rect<> (&rectangle_array)[N]);
    template<usize N> inline void _rectLinesN(Rect<> (&rectangle_array)[N]);

public:
    using Cfg = M_Cfg;

    explicit Renderer(Cfg config = Cfg{});
    ~Renderer();
    Renderer(Renderer&& other) noexcept;
    Renderer& operator= (Renderer&& other) noexcept;
    // delete
    Renderer (const Renderer& copy_ctor) = delete;
    Renderer& operator= (const Renderer& copy_operator) = delete;

    Renderer create(void* window_ptr);
    void destroy();
    bool exists();

    Renderer& setVsync(bool enabled = true);

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
    void rectFill(Rect<> rectangle, ColorU8 color);
    void rectFill(Rect<> rectangle, ColorF32 color);
    void rectLines(Rect<> rectangle, ColorU8 color);
    void rectLines(Rect<> rectangle, ColorF32 color);
    template<usize N> void rectFillN(Rect<> (&rectangle_array)[N], ColorU8 color);
    template<usize N> void rectFillN(Rect<> (&rectangle_array)[N], ColorF32 color);
    template<usize N> void rectLinesN(Rect<> (&rectangle_array)[N], ColorU8 color);
    template<usize N> void rectLinesN(Rect<> (&rectangle_array)[N], ColorF32 color);
    //
    void PolyFill(Vec2f size, Vec2f pos, ColorU8 color);
    void PolyLines(Vec2f size, Vec2f pos, ColorU8 color);
    //
    void circleFill(Vec2f size, Vec2f pos, ColorU8 color);
    void circleLines(Vec2f size, Vec2f pos, ColorU8 color);
};

NAMESPACE_END(cone)
