#pragma once
#include "vexa/core/StaticPimpl.hpp"
#include "Renderer.hpp"
NAMESPACE_BEGIN(vexa)

class VX_NODISCARD Window
{
public:
    enum Trait : uint64;

private:
    class Impl;
    StaticPimpl<Impl, 40, true> m;


    class VX_NODISCARD M_Cfg
    {
        friend class Window;

    public:
        CfgVal<Flags<Trait>> flags;
        //
        CfgVal<const char*> title;
        CfgVal<Vec2i> size;
        CfgVal<Vec2i> pos;
        CfgVal<Vec2> aspect_ratio;
        CfgVal<const char*> icon_image_path;
        //
        CfgVal<bool> is_resizable;
        CfgVal<bool> is_maximized;
        CfgVal<bool> is_minimized;
        CfgVal<bool> is_fullscreen;
        CfgVal<bool> is_borderless;
        CfgVal<bool> is_hidden;
        CfgVal<bool> is_on_top;
        CfgVal<bool> is_mouse_grabbed;
        CfgVal<bool> is_mouse_relative;
        CfgVal<bool> is_keyboard_grabbed;

        constexpr M_Cfg():
            flags(CfgVal<Flags<Trait>>{Trait{}}),

            title(""),
            size(Vec2i{0, 0}),
            pos(Vec2i{0, 0}),
            aspect_ratio(Vec2{1, 1}),
            icon_image_path(nullptr),
            is_resizable(false),
            is_maximized(false),
            is_minimized(false),
            is_fullscreen(false),
            is_borderless(false),
            is_hidden(false),
            is_on_top(false),
            is_mouse_grabbed(false),
            is_mouse_relative(false),
            is_keyboard_grabbed(false)
        {}

        M_Cfg& reset() {
            flags.reset();
            title.reset();
            size.reset();
            pos.reset();
            aspect_ratio.reset();
            icon_image_path.reset();
            is_resizable.reset();
            is_maximized.reset();
            is_minimized.reset();
            is_fullscreen.reset();
            is_borderless.reset();
            is_hidden.reset();
            is_on_top.reset();
            is_mouse_grabbed.reset();
            is_mouse_relative.reset();
            is_keyboard_grabbed.reset();
            return *this;
        }
    }
    m_bconfig;


    using mWindowPtr = void*;
    using mSurface = void*;
    using mWindowFlags = uint64;
    //
    static mWindowFlags m_getActiveFlags(mWindowPtr win);



    // wrap SDL function that takes extra arguments after the window pointer
    template<typename... Args>
    void m_trySetWithArgs(
        const char* prop, auto& build_config_var, auto config_val,
        auto (*sdl_fn), Args... sdl_fn_args
    );

    // wrap SDL function that takes only the window pointer
    void m_trySetNoArgs(
        const char* prop, auto& build_config_var, auto config_val,
        auto (*sdl_fn)
    );


public:
    using Cfg = M_Cfg;

    // Window() = delete;
    Window(Cfg config = Cfg{});
    // rule of 5
    ~Window();
    Window(Window&& other);
    Window& operator= (Window&& other);
    Window(Window& other) = delete;
    Window& operator= (const Window& copy_ctor) = delete;

    Window create();
    void destroy();
    bool exists();
    uint32 id() const;

    Renderer& renderer();
    const char* title();
    Vec2i size();
    Vec2i position();
    Vec2 aspectRatio();
    bool isResizable() const;
    bool isMaximized() const;
    bool isMinimized() const;
    bool isFullScreen() const;
    bool isBorderless() const;
    bool isHidden() const;
    bool isAlwaysOnTop() const;
    bool isKeyboardGrabbed() const;
    bool isMouseGrabbed() const;
    bool isMouseRelative() const;


    Window& setRenderer(const Renderer::Cfg& renderer_cfg);
    Window& setTitle(const char* title);
    Window& setSize(Vec2i size);
    Window& setPosition(Vec2i position);
    Window& setAspectRatio(fp32 min_ratio, fp32 max_ratio);
    Window& setAspectRatio(fp32 ratio);  // overload: calls the main one
    Window& setIcon(const char* image_path);
    Window& setResizable(bool yes = true);
    Window& setMaximized(bool yes = true);  Window& toggleMaximized();
    Window& setMinimized(bool yes = true);
    Window& setFullScreen(bool yes = true);
    Window& setBorderless(bool yes = true);
    Window& setHidden(bool yes = true);
    Window& setAlwaysOnTop(bool yes = true);
    Window& setKeyboardGrabbed(bool yes = true);
    Window& setMouseGrabbed(bool yes = true);
    Window& setMouseRelative(bool yes = true);

private:
    template<Trait> consteval static uint64 M_ToSDL3WindowFlag();
    static uint64 M_ToSDL3WindowFlagRuntime(uint64 traits);
};


enum Window::Trait : uint64 {
    NONE = 0,

    /* general */
    TRANSPARENT = 1 << 1,
    UNFOCUSABLE = 1 << 2,
    DENSE_PIXELS = 1 << 3,

    /* meta */
    SKIP_TASKBAR = 1 << 10,
    TOOLTIP_MENU = 1 << 11,
    POPUP_MENU = 1 << 12,
    EXTERN = 1 << 13,

    /* platform */
    OPENGL = 1 << 20,
    VULKAN = 1 << 21,
    METAL = 1 << 22,
};


GEN_BITOPS(Window::Trait, enum_t<Window::Trait>);


NAMESPACE_END(vexa)
