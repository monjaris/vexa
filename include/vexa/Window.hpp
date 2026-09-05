#pragma once
#include "Renderer.hpp"
NAMESPACE_BEGIN(vexa)

class VX_NODISCARD Window
{
public:
    enum Trait : uint64;

private:
    class Impl;
    Uptr<Impl> impl;


    class VX_NODISCARD M_Cfg
    {
        friend class Window;

        CfgVal<Flags<Trait>> m_flags;
        //
        CfgVal<const char*> m_title;
        CfgVal<Vec2i> m_size;
        CfgVal<Vec2i> m_pos;
        CfgVal<Vec2> m_aspect_ratio;
        CfgVal<const char*> m_icon_image_path;
        //
        CfgVal<bool> m_is_resizable;
        CfgVal<bool> m_is_maximized;
        CfgVal<bool> m_is_minimized;
        CfgVal<bool> m_is_fullscreen;
        CfgVal<bool> m_is_borderless;
        CfgVal<bool> m_is_hidden;
        CfgVal<bool> m_is_on_top;
        CfgVal<bool> m_is_mouse_grabbed;
        CfgVal<bool> m_is_mouse_relative;
        CfgVal<bool> m_is_keyboard_grabbed;

    public:
        constexpr M_Cfg() noexcept:
            m_flags(CfgVal<Flags<Trait>>{Trait{}}),

            m_title(""),
            m_size(Vec2i{0, 0}),
            m_pos(Vec2i{0, 0}),
            m_aspect_ratio(Vec2{1, 1}),
            m_icon_image_path(nullptr),
            m_is_resizable(false),
            m_is_maximized(false),
            m_is_minimized(false),
            m_is_fullscreen(false),
            m_is_borderless(false),
            m_is_hidden(false),
            m_is_on_top(false),
            m_is_mouse_grabbed(false),
            m_is_mouse_relative(false),
            m_is_keyboard_grabbed(false)
        {}

        auto flags() -> decltype(m_flags) {
            return m_flags;
        }

        M_Cfg& reset() {
            m_flags = m_flags.defaultVal();
            m_title = m_title.defaultVal();
            m_size = m_size.defaultVal();
            m_pos = m_pos.defaultVal();
            m_aspect_ratio = m_aspect_ratio.defaultVal();
            m_icon_image_path = m_icon_image_path.defaultVal();
            m_is_resizable = m_is_resizable.defaultVal();
            m_is_maximized = m_is_maximized.defaultVal();
            m_is_minimized = m_is_minimized.defaultVal();
            m_is_fullscreen = m_is_fullscreen.defaultVal();
            m_is_borderless = m_is_borderless.defaultVal();
            m_is_hidden = m_is_hidden.defaultVal();
            m_is_on_top = m_is_on_top.defaultVal();
            m_is_mouse_grabbed = m_is_mouse_grabbed.defaultVal();
            m_is_mouse_relative = m_is_mouse_relative.defaultVal();
            m_is_keyboard_grabbed = m_is_keyboard_grabbed.defaultVal();
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
    ) noexcept;

    // wrap SDL function that takes only the window pointer
    void m_trySetNoArgs(
        const char* prop, auto& build_config_var, auto config_val,
        auto (*sdl_fn)
    ) noexcept;


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
    uint32 id() const noexcept;

    Renderer& renderer() noexcept;
    const char* title();
    Vec2i size();
    Vec2i position();
    bool isResizable();
    bool isMaximized();
    bool isMinimized();
    bool isFullScreen();
    bool isBorderless();
    bool isHidden();
    bool isAlwaysOnTop();
    bool isKeyboardGrabbed();
    bool isMouseGrabbed();
    bool isMouseRelative();


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


enum VX_NODISCARD Window::Trait : uint64 {
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
