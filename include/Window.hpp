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

        CfgVal<Flags<Trait>> flags;
        //
        CfgVal<const char*> title;
        CfgVal<Vec2i> size;
        CfgVal<Vec2i> position;
        CfgVal<bool> is_resizable;
        CfgVal<bool> is_maximized;
        CfgVal<bool> is_minimized;
        CfgVal<bool> is_fullscreen;
        CfgVal<bool> is_borderless;
        CfgVal<bool> is_hidden;
        CfgVal<bool> is_always_on_top;
        CfgVal<bool> is_mouse_grabbed;
        CfgVal<bool> is_mouse_relative;
        CfgVal<bool> is_keyboard_grabbed;

    public:
        constexpr M_Cfg() noexcept:
            flags(CfgVal<Flags<Trait>>{Trait{}}),

            title(""),
            size(Vec2i{0, 0}),
            position(Vec2i{0, 0}),
            is_resizable(false),
            is_maximized(false),
            is_minimized(false),
            is_fullscreen(false),
            is_borderless(false),
            is_hidden(false),
            is_always_on_top(false),
            is_mouse_grabbed(false),
            is_mouse_relative(false),
            is_keyboard_grabbed(false)
        {}

        M_Cfg& reset() {
            flags = flags.defaultVal();
            title = title.defaultVal();
            size = size.defaultVal();
            position = position.defaultVal();
            is_resizable = is_resizable.defaultVal();
            is_maximized = is_maximized.defaultVal();
            is_minimized = is_minimized.defaultVal();
            is_fullscreen = is_fullscreen.defaultVal();
            is_borderless = is_borderless.defaultVal();
            is_hidden = is_hidden.defaultVal();
            is_always_on_top = is_always_on_top.defaultVal();
            is_mouse_grabbed = is_mouse_grabbed.defaultVal();
            is_mouse_relative = is_mouse_relative.defaultVal();
            is_keyboard_grabbed = is_keyboard_grabbed.defaultVal();
            return *this;
        }
    }
    m_build_config;


    using mWindowPtr = void*;
    using mWindowFlags = uint64;
    static mWindowFlags _getActiveFlags(mWindowPtr win);
    static void _trySetTitle(mWindowPtr win, const char* title);
    static void _trySetSize(mWindowPtr win, int x, int y);
    static void _trySetPos(mWindowPtr win, int x, int y);
    static void _trySetResizable(mWindowPtr win, bool yes);
    static void _trySetMinimized(mWindowPtr win, bool yes);
    static void _trySetMaximized(mWindowPtr win, bool yes);
    static void _trySetFullscreen(mWindowPtr win, bool yes);
    static void _trySetBorderless(mWindowPtr win, bool yes);
    static void _trySetHidden(mWindowPtr win, bool yes);
    static void _trySetAlwaysOnTop(mWindowPtr win, bool yes);
    static void _trySetMouseGrabbed(mWindowPtr win, bool yes);
    static void _trySetMouseRelative(mWindowPtr win, bool yes);
    static void _trySetKeyboardGrabbed(mWindowPtr win, bool yes);


public:
    using Cfg = M_Cfg;

    Window(Cfg config = Cfg{});
    ~Window();
    Window(Window&& other);
    Window& operator= (Window&& other);
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


    Window& setRenderer(const Renderer::Cfg& recreatenderer_cfg);
    Window& setTitle(const char* title);
    Window& setSize(Vec2i size);
    Window& setPosition(Vec2i position);
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
    template<Trait> consteval static inline uint64 M_ToSDL3WindowFlag();
    static inline uint64 M_ToSDL3WindowFlagRuntime(uint64 traits);
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


NAMESPACE_END(vexa)
