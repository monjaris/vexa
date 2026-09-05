#pragma once
#include "vexa/core/common.hpp"
#include "vexa/alt/memory.hpp"
#include "Texture.hpp"
#include "Font.hpp"
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
        CfgVal<uint8> mode;

    public:
        constexpr M_Cfg () noexcept:
            vsync(false),
            mode(0)
        {}

        void reset() noexcept {
            vsync = vsync.defaultVal();
        }
    }
    m_bconfig;


public:
    enum class Mode : uint8
    {
        NONE = 0,
        STRETCH = 1,
        LETTERBOX = 2,
        OVERSCAN = 3,
        INTEGER_SCALE = 4
    };
    using enum Mode;

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
    bool vsync();
    void setMode(Mode render_mode);
    Mode mode();

    void start();  // sets color black
    void start(nullptrT null);  // edge-case, if you really want to keep the last used brush color
    void start(Color color);
    void start(ColorF32 color);
    void finish();

    // create texture from image
    Texture loadTexture(Image&& image) noexcept;
    // create texture from font
    Texture loadTexture(Font& font, uint64 font_ize, const char* text) noexcept;

    void drawTexture(const Texture& texture, Vec2 pos);
    void drawTexture(const Texture& texture, Vec2 pos, Color color);
    void drawTexture(const Texture& texture, Rect src, Rect dest);
    void drawTexture(const Texture& texture, Rect src, Rect dest, Color color);

    void drawText(Font& font, const char* text, Vec2 pos, Color color);

    void triangleFill(Triangle triangle, Color color);
    void triangleFill(Triangle triangle, ColorF32 color);
    void triangleLines(Triangle triangle, Color color);
    void triangleLines(Triangle triangle, ColorF32 color);
    template<usize N> void triangleFillN(Triangle (&triangle_array)[N], Color color);
    template<usize N> void triangleFillN(Triangle (&triangle_array)[N], ColorF32 color);
    template<usize N> void triangleLinesN(Triangle (&triangle_array)[N], Color color);
    template<usize N> void triangleLinesN(Triangle (&triangle_array)[N], ColorF32 color);
    //
    void rectFill(Rect rectangle, Color color);
    void rectFill(Rect rectangle, ColorF32 color);
    void rectLines(Rect rectangle, Color color);
    void rectLines(Rect rectangle, ColorF32 color);
    template<usize N> void rectFillN(Rect (&rectangle_array)[N], Color color);
    template<usize N> void rectFillN(Rect (&rectangle_array)[N], ColorF32 color);
    template<usize N> void rectLinesN(Rect (&rectangle_array)[N], Color color);
    template<usize N> void rectLinesN(Rect (&rectangle_array)[N], ColorF32 color);
    //
    void PolyFill(Vec2 pos, Vec2 size, Color color);
    void PolyLines(Vec2 pos, Vec2 size, Color color);
    //
    void circleFill(Circle circle, ColorF32 color, fp32 quality = Circle::NORMAL);
    void circleFill(Circle circle, Color color, fp32 quality = Circle::NORMAL);
    void circleLines(Circle circle, Color color);
    void circleLines(Circle circle, ColorF32 color);
};



NAMESPACE_END(vexa)
