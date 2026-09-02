#include "vexa/alt/SDL3.h"
#include "vexa/Window.hpp"
NAMESPACE_BEGIN(vexa)

#define FN "Window::{}(): "

#define DEF_MSG static constexpr inline const char* const
    DEF_MSG mf_failed_to_create_window
        { "an error occured while creating the renderer" };

    DEF_MSG mf_window_never_existed_before
        { "invalid call on a window that has never been created" };

    DEF_MSG mf_window_currently_doesnt_exist
        { "invalid call on an already destroyed window" };

    DEF_MSG mf_renderer_doesnt_exist
        { "window doesn't have a renderer" };

    DEF_MSG me_window_already_exists
        { "renderer already exists" };

    DEF_MSG me_failed_to_create_input_ctx
        { "an error occured while creating the input context" };

#undef DEF_MSG



using This = Window;


NAMESPACE_BEGIN()
using enum Window::Trait;

struct TraitMap {
    This::Trait trait;
    uint64 flag;
};


static constexpr TraitMap flag_maps[] = {
    // { RESIZABLE,     SDL_WINDOW_RESIZABLE },
    // { MINIMIZED,     SDL_WINDOW_MINIMIZED },
    // { MAXIMIZED,     SDL_WINDOW_MAXIMIZED },
    // { FULLSCREEN,    SDL_WINDOW_FULLSCREEN },
    // { BORDERLESS,    SDL_WINDOW_BORDERLESS },
    // { HIDDEN,        SDL_WINDOW_HIDDEN },
    { TRANSPARENT,   SDL_WINDOW_TRANSPARENT },
    // { ALWAYS_ON_TOP, SDL_WINDOW_ALWAYS_ON_TOP },
    { UNFOCUSABLE,   SDL_WINDOW_NOT_FOCUSABLE },
    { DENSE_PIXELS,  SDL_WINDOW_HIGH_PIXEL_DENSITY },
    // { INPUT_FOCUS,      SDL_WINDOW_INPUT_FOCUS },
    // { MOUSE_GRABBED,    GRABBED },
    // { MOUSE_FOCUS,      SDL_WINDOW_MOUSE_FOCUS },
    // { MOUSE_CAPTURE,    SDL_WINDOW_MOUSE_CAPTURE },
    // { MOUSE_RELATIVE,   SDL_WINDOW_MOUSE_RELATIVE_MODE },
    // { KEYBOARD_GRABBED, SDL_WINDOW_KEYBOARD_GRABBED },
    // { OCCLUDED,     SDL_WINDOW_OCCLUDED },
    // { MODAL,        SDL_WINDOW_MODAL },
    { SKIP_TASKBAR, SDL_WINDOW_UTILITY },
    { TOOLTIP_MENU, SDL_WINDOW_TOOLTIP },
    { POPUP_MENU,   SDL_WINDOW_POPUP_MENU },
    // { FILL_DOC,     SDL_WINDOW_FILL_DOCUMENT },
    { OPENGL, SDL_WINDOW_OPENGL },
    { VULKAN, SDL_WINDOW_VULKAN },
    { METAL,  SDL_WINDOW_METAL },
    { EXTERN, SDL_WINDOW_EXTERNAL },
};

NAMESPACE_END()




//  IMPL  //

class This::Impl {
    SDL_Window* m_window = nullptr;
    uint32 m_id = 0;
public:
    bool window_ever_existed = false;
    bool window_exists = false;
    Renderer renderer = Renderer{};
    bool renderer_set = false;

    explicit Impl() = default;

    ~Impl() {
        if (window_exists) {
            SDL_DestroyWindow(m_window);
            window_exists = false;
        }
    }

    SDL_Window* ptr() { return m_window; }

    SDL_Window* createWindow(Cfg config) {
        if (!window_exists)
        {
            m_window = SDL_CreateWindow(
                config.m_title, config.m_size->x, config.m_size->y,
                This::M_ToSDL3WindowFlagRuntime(config.m_flags->value())
            );
            IF_THEN(!m_window,   log::fatal(FN"{}", __func__, mf_failed_to_create_window);)

            m_id = SDL_GetWindowID(m_window);
            window_ever_existed = window_exists = true;
        }
        else { log::error(FN"{}", __func__, me_window_already_exists); }

        return m_window;
    }

    bool createInputCtx() {
        return SDL_StartTextInputWithProperties(m_window, 0);
    }
};


This::Window(Cfg config): impl(new Impl{}), m_bconfig(config) {}

This::~Window() { impl = nullptr; }

This::Window(Window&& other) {
    impl = std::move(other.impl);
    m_bconfig = other.m_bconfig;
}

Window& This::operator= (Window&& other) {
    impl = std::move(other.impl);
    m_bconfig = other.m_bconfig;
    return *this;
}




//  PRIVATE  //

template<This::Trait traits>
consteval inline uint64 This::M_ToSDL3WindowFlag() {
    uint64 sdl_flags = 0;
    for (const auto& m : flag_maps) {
        if (traits & m.trait) sdl_flags |= m.flag;
    }
    return sdl_flags;
}

uint64 This::M_ToSDL3WindowFlagRuntime(uint64 traits) {
    uint64 sdl_flags = 0;
    for (const auto& m : flag_maps) {
        if (traits & static_cast<uint64>(m.trait)) sdl_flags |= m.flag;
    }
    return sdl_flags;
}

This::mWindowFlags This::m_getActiveFlags(mWindowPtr win) {
    return SDL_GetWindowFlags((SDL_Window*)win);
}

template<typename... Args>
void This::m_trySetWithArgs(
    const char* prop, auto& build_config_var, auto config_val,
    auto (*sdl_fn), Args... sdl_fn_args
) noexcept
{
    if (impl && impl->window_exists) {
        if (sdl_fn(impl->ptr(), sdl_fn_args...) == false) {
            log::error("Failed to set {} property", prop);
        }
    }
    build_config_var = config_val;
}

void This::m_trySetNoArgs(
    const char* prop, auto& build_config_var, auto config_val,
    auto (*sdl_fn)
) noexcept
{
    if (impl && impl->window_exists) {
        if (sdl_fn(impl->ptr()) == false) {
            log::error("Failed to set {} property", prop);
        }
    }
    build_config_var = config_val;
}





//  GENERAL METHODS  //

#define IS_CFG_DEFAULT(_cfg_prop) \
    (m_bconfig._cfg_prop == m_bconfig._cfg_prop.defaultVal())

Window This::create() {
    Window build = {};
    build.m_bconfig = m_bconfig;
    auto& cfg = build.m_bconfig;

    auto* new_window = build.impl->createWindow(build.m_bconfig);
    IF_THEN (!new_window,   log::fatal(FN"{}", __func__, mf_window_currently_doesnt_exist);)
    auto new_window_id = SDL_GetWindowID(new_window);
    log::info(FN"created new window [ID={}]", __func__, new_window_id);

    IF_THEN(!build.impl->createInputCtx(),
        log::error(FN"{} [ID={}]", __func__, me_failed_to_create_input_ctx, new_window_id);
    );

    if (!IS_CFG_DEFAULT(m_title))
        build.setTitle(cfg.m_title);
    if (!IS_CFG_DEFAULT(m_size))
        build.setSize(cfg.m_size);
    if (!IS_CFG_DEFAULT(m_pos))
        build.setPosition(cfg.m_pos);
    if (!IS_CFG_DEFAULT(m_aspect_ratio))
        build.setAspectRatio(cfg.m_aspect_ratio->x, cfg.m_aspect_ratio->y);
    if (!IS_CFG_DEFAULT(m_icon))
        build.setIcon(cfg.m_icon);
    if (!IS_CFG_DEFAULT(m_is_resizable))
        build.setResizable(cfg.m_is_resizable);
    if (!IS_CFG_DEFAULT(m_is_minimized))
        build.setMinimized(cfg.m_is_minimized);
    if (!IS_CFG_DEFAULT(m_is_maximized))
        build.setMaximized(cfg.m_is_maximized);
    if (!IS_CFG_DEFAULT(m_is_fullscreen))
        build.setFullScreen(cfg.m_is_fullscreen);
    if (!IS_CFG_DEFAULT(m_is_borderless))
        build.setBorderless(cfg.m_is_borderless);
    if (!IS_CFG_DEFAULT(m_is_hidden))
        build.setHidden(cfg.m_is_hidden);
    if (!IS_CFG_DEFAULT(m_is_on_top))
        build.setAlwaysOnTop(cfg.m_is_on_top);
    if (!IS_CFG_DEFAULT(m_is_mouse_grabbed))
        build.setMouseGrabbed(cfg.m_is_mouse_grabbed);
    if (!IS_CFG_DEFAULT(m_is_mouse_relative))
        build.setMouseRelative(cfg.m_is_mouse_relative);
    if (!IS_CFG_DEFAULT(m_is_keyboard_grabbed))
        build.setKeyboardGrabbed(cfg.m_is_keyboard_grabbed);

    if (impl->renderer_set) {
        build.impl->renderer = build.impl->renderer.create((SDL_Window*)new_window);
    }
    return build;
}



void This::destroy() {
    impl = nullptr;
    m_bconfig.reset();
}


bool This::exists() {
    return impl->window_exists;
}


uint32 This::id() const noexcept {
    return SDL_GetWindowID(impl->ptr());
}


Renderer& This::renderer() noexcept {
    IF_THEN(!impl,
        log::fatal(FN"{}", __func__, mf_window_never_existed_before);
    );
    IF_THEN(!impl->window_ever_existed,
        log::fatal(FN"{}", __func__, mf_window_never_existed_before);
    )
    IF_THEN(!impl->window_exists,
        log::fatal(FN"{}", __func__, mf_window_never_existed_before);
    )
    IF_THEN(!impl->renderer.exists(),
        log::error(FN"{}", __func__, mf_renderer_doesnt_exist);
    )
    return impl->renderer;
}

const char* This::title() {
    return SDL_GetWindowTitle(impl->ptr());
}

Vec2i This::size() {
    SDL_GetWindowSize(impl->ptr(), &m_bconfig.m_size->x, &m_bconfig.m_size->y);
    return m_bconfig.m_size;
}

Vec2i This::position() {
    SDL_GetWindowPosition(impl->ptr(), &m_bconfig.m_pos->x, &m_bconfig.m_pos->y);
    return m_bconfig.m_pos;
}

bool This::isResizable() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_RESIZABLE);
}

bool This::isMaximized() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_MAXIMIZED);
}

bool This::isMinimized() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_MINIMIZED);
}

bool This::isFullScreen() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_FULLSCREEN);
}

bool This::isBorderless() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_BORDERLESS);
}

bool This::isHidden() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_HIDDEN);
}

bool This::isAlwaysOnTop() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_ALWAYS_ON_TOP);
}

bool This::isKeyboardGrabbed() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool This::isMouseRelative() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_MOUSE_RELATIVE_MODE);
}

bool This::isMouseGrabbed() {
    return (m_getActiveFlags(impl->ptr()) & SDL_WINDOW_MOUSE_GRABBED);
}











//  SETTERS //


Window& This::setRenderer(const Renderer::Cfg& renderer_cfg) {
    impl->renderer_set = true;
    impl->renderer.m_build_config = renderer_cfg;
    if (impl && impl->window_exists) {
        impl->renderer = impl->renderer.create(impl->ptr());
    }
    return *this;
}

Window& This::setTitle(const char* title) {
    m_trySetWithArgs("title", m_bconfig.m_title, title,
                        SDL_SetWindowTitle, title);
    return *this;
}

Window& This::setSize(Vec2i size) {
    m_trySetWithArgs("size", m_bconfig.m_size, size,
                        SDL_SetWindowSize, size.x, size.y);
    return *this;
}

Window& This::setPosition(Vec2i position) {
    m_trySetWithArgs("position", m_bconfig.m_pos, position,
                        SDL_SetWindowPosition, position.x, position.y);
    return *this;
}

Window& This::setAspectRatio(fp32 min, fp32 max) {
    m_trySetWithArgs("aspect-ratio", m_bconfig.m_aspect_ratio, Vec2{min, max},
                        SDL_SetWindowAspectRatio, min, max);
    return *this;
}

Window& This::setIcon(Image image) {
    m_trySetWithArgs("icon", m_bconfig.m_icon, image,
                        SDL_SetWindowIcon, (SDL_Surface*)image.ptr());
    return *this;
}

Window& This::setResizable(bool yes) {
    m_trySetWithArgs("is-resizable", m_bconfig.m_is_resizable, yes,
                        SDL_SetWindowResizable, yes);
    return *this;
}

Window& This::setMaximized(bool yes) {
    m_trySetNoArgs("is-maximized", m_bconfig.m_is_maximized, yes,
                    yes ? SDL_MaximizeWindow : SDL_RestoreWindow);
    return *this;
}

Window& This::toggleMaximized() {
    setMaximized(!(m_getActiveFlags(impl->ptr()) & SDL_WINDOW_MAXIMIZED));
    return *this;
}

Window& This::setMinimized(bool yes) {
    m_trySetNoArgs("is-minimized", m_bconfig.m_is_minimized, yes,
                    yes ? SDL_MinimizeWindow : SDL_RestoreWindow);
    return *this;
}

Window& This::setFullScreen(bool yes) {
    m_trySetWithArgs("is-fullscreen", m_bconfig.m_is_fullscreen, yes,
                        SDL_SetWindowFullscreen, yes);
    return *this;
}

Window& This::setBorderless(bool yes) {
    m_trySetWithArgs("is-borderless", m_bconfig.m_is_borderless, yes,
                        SDL_SetWindowBordered, !yes);
    return *this;
}

Window& This::setHidden(bool yes) {
    m_trySetNoArgs("is-hidden", m_bconfig.m_is_hidden, yes,
                    yes ? SDL_HideWindow : SDL_ShowWindow);
    return *this;
}

Window& This::setAlwaysOnTop(bool yes) {
    m_trySetWithArgs("is-always-on-top", m_bconfig.m_is_on_top, yes,
                        SDL_SetWindowAlwaysOnTop, yes);
    return *this;
}

Window& This::setKeyboardGrabbed(bool yes) {
    m_trySetWithArgs("is-keyboard-grabbed", m_bconfig.m_is_keyboard_grabbed, yes,
                        SDL_SetWindowKeyboardGrab, yes);
    return *this;
}

Window& This::setMouseGrabbed(bool yes) {
    m_trySetWithArgs("is-mouse-grabbed", m_bconfig.m_is_mouse_grabbed, yes,
                        SDL_SetWindowMouseGrab, yes);
    return *this;
}

Window& This::setMouseRelative(bool yes) {
    m_trySetWithArgs("is-mouse-relative", m_bconfig.m_is_mouse_relative, yes,
                        SDL_SetWindowRelativeMouseMode, yes);
    return *this;
}



NAMESPACE_END(vexa)
