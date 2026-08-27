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

This::Window(Cfg config): impl(new Impl{}), m_build_config(config) {}
This::~Window() { impl = nullptr; }

This::Window(Window&& other) {
    impl = std::move(other.impl);
    m_build_config = other.m_build_config;
}

Window& This::operator= (Window&& other) {
    impl = std::move(other.impl);
    m_build_config = other.m_build_config;
    return *this;
}



#define IS_CFG_DEFAULT(_cfg_prop)  (m_build_config._cfg_prop == m_build_config._cfg_prop.defaultVal())

Window This::create() {
    Window build = {};
    build.m_build_config = m_build_config;

    auto* new_window = build.impl->createWindow(build.m_build_config);
    IF_THEN (!new_window,   log::fatal(FN"{}", __func__, mf_window_currently_doesnt_exist);)
    auto new_window_id = SDL_GetWindowID(new_window);
    log::info(FN"created new window [ID={}]", __func__, new_window_id);

    IF_THEN(!build.impl->createInputCtx(),
        log::error(FN"{} [ID={}]", __func__, me_failed_to_create_input_ctx, new_window_id);
    );

    if (!IS_CFG_DEFAULT(m_title))
        _trySetTitle(new_window, m_build_config.m_title);
    if (!IS_CFG_DEFAULT(m_size))
        _trySetSize(new_window, m_build_config.m_size->x, m_build_config.m_size->y);
    if (!IS_CFG_DEFAULT(m_position))
        _trySetPos(new_window, m_build_config.m_position->x, m_build_config.m_position->y);
    if (!IS_CFG_DEFAULT(m_is_resizable))
        _trySetResizable(new_window, m_build_config.m_is_resizable);
    if (!IS_CFG_DEFAULT(m_is_minimized))
        _trySetMinimized(new_window, m_build_config.m_is_minimized);
    if (!IS_CFG_DEFAULT(m_is_maximized))
        _trySetMaximized(new_window, m_build_config.m_is_maximized);
    if (!IS_CFG_DEFAULT(m_is_fullscreen))
        _trySetFullscreen(new_window, m_build_config.m_is_fullscreen);
    if (!IS_CFG_DEFAULT(m_is_borderless))
        _trySetBorderless(new_window, m_build_config.m_is_borderless);
    if (!IS_CFG_DEFAULT(m_is_hidden))
        _trySetHidden(new_window, m_build_config.m_is_hidden);
    if (!IS_CFG_DEFAULT(m_is_always_on_top))
        SDL_SetWindowAlwaysOnTop(new_window, m_build_config.m_is_always_on_top);
    if (!IS_CFG_DEFAULT(m_is_mouse_grabbed))
        SDL_SetWindowMouseGrab(new_window, m_build_config.m_is_mouse_grabbed);
    if (!IS_CFG_DEFAULT(m_is_mouse_relative))
        SDL_SetWindowRelativeMouseMode(new_window, m_build_config.m_is_mouse_relative);
    if (!IS_CFG_DEFAULT(m_is_keyboard_grabbed))
        _trySetKeyboardGrabbed(new_window, m_build_config.m_is_keyboard_grabbed);

    if (impl->renderer_set) {
        build.impl->renderer = build.impl->renderer.create((SDL_Window*)new_window);
    }
    return build;
}


void This::destroy() {
    impl = nullptr;
    m_build_config.reset();
}


bool This::exists() {
    return impl->window_exists;
}


// Flags This::defaultFlags() const noexcept {
//     return m_config.flags.defaultVal();
// }

// const Flags& This::flags() noexcept {
//     return m_config.flags;
// }


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
    SDL_GetWindowSize(impl->ptr(), &m_build_config.m_size->x, &m_build_config.m_size->y);
    return m_build_config.m_size;
}

Vec2i This::position() {
    SDL_GetWindowPosition(impl->ptr(), &m_build_config.m_position->x, &m_build_config.m_position->y);
    return m_build_config.m_position;
}

bool This::isResizable() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_RESIZABLE);
}

bool This::isMaximized() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_MAXIMIZED);
}

bool This::isMinimized() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_MINIMIZED);
}

bool This::isFullScreen() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_FULLSCREEN);
}

bool This::isBorderless() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_BORDERLESS);
}

bool This::isHidden() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_HIDDEN);
}

bool This::isAlwaysOnTop() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_ALWAYS_ON_TOP);
}

bool This::isKeyboardGrabbed() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool This::isMouseRelative() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_MOUSE_RELATIVE_MODE);
}

bool This::isMouseGrabbed() {
    return (_getActiveFlags(impl->ptr()) & SDL_WINDOW_MOUSE_GRABBED);
}





This::mWindowFlags This::_getActiveFlags(mWindowPtr win) {
    return SDL_GetWindowFlags((SDL_Window*)win);
}


#define TRY_SET_FAILED(_prop)  "Failed to set " _prop " property "

void This::_trySetTitle(This::mWindowPtr win, const char* title) {
    if (!SDL_SetWindowTitle((SDL_Window*)win, title)) {
        log::error(TRY_SET_FAILED("title") "to \"{}\"", title);
    }
}

void This::_trySetSize(This::mWindowPtr win, int x, int y) {
    if (!SDL_SetWindowSize((SDL_Window*)win, x, y)) {
        log::error(TRY_SET_FAILED("size") "to {{{},{}}}", x, y);
    }
}

void This::_trySetPos(This::mWindowPtr win, int x, int y) {
    if (!SDL_SetWindowPosition((SDL_Window*)win, x, y)) {
        log::error(
            TRY_SET_FAILED("position") "to {{{}, {}}}, "
            "Hence, are you on wayland?", x, y
        );
    }
}

void This::_trySetAspectRatio(This::mWindowPtr win, fp32 min, fp32 max) {
    if (!SDL_SetWindowAspectRatio((SDL_Window*)win, min, max)) {
        log::error(
            TRY_SET_FAILED("aspect-ratio") "to {{{}, {}}}, "
            "Hence, are you on wayland?", min, max
        );
    }
}


void This::_trySetResizable(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowResizable((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-resizable") "to {}", yes);
    }
}

void This::_trySetMinimized(This::mWindowPtr win, bool yes) {
    if (yes) {
        if (!SDL_MinimizeWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-minimized") "to {}", true);
        }
    }
    else {
        if (!SDL_RestoreWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-minimized") "to {}", false);
        }
    }
}

void This::_trySetMaximized(This::mWindowPtr win, bool yes) {
    if (yes) {
        if (!SDL_MaximizeWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-maximized") "to {}", true);
        }
    }
    else {
        if (!SDL_RestoreWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-maximized") "to {}", false);
        }
    }
}

void This::_trySetFullscreen(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowFullscreen((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-fullscreen") "to {}", yes);
    }
}

void This::_trySetBorderless(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowBordered((SDL_Window*)win, !yes)) {
        log::error(TRY_SET_FAILED("is-borderless") "to {}", !yes);
    }
}

void This::_trySetHidden(This::mWindowPtr win, bool yes) {
    if (yes) {
        if (!SDL_HideWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-hidden") "to {}", true);
        }
    }
    else {
        if (!SDL_ShowWindow((SDL_Window*)win)) {
            log::error(TRY_SET_FAILED("is-hidden") "to {}", false);
        }
    }
}

void This::_trySetAlwaysOnTop(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowAlwaysOnTop((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-always-on-top") "to {}", yes);
    }
}

void This::_trySetKeyboardGrabbed(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowKeyboardGrab((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-keyboard-grabbed") "to {}", yes);
    }
}

void This::_trySetMouseGrabbed(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowMouseGrab((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-mouse-grabbed") "to {}", yes);
    }
}

void This::_trySetMouseRelative(This::mWindowPtr win, bool yes) {
    if (!SDL_SetWindowRelativeMouseMode((SDL_Window*)win, yes)) {
        log::error(TRY_SET_FAILED("is-mouse-relative") "to {}", yes);
    }
}



Window& This::setRenderer(const Renderer::Cfg& renderer_cfg) {
    impl->renderer_set = true;
    impl->renderer.m_build_config = renderer_cfg;
    if (impl && impl->window_exists) { impl->renderer = impl->renderer.create(impl->ptr()); }
    return *this;
}

Window& This::setTitle(const char* title) {
    if (impl && impl->window_exists) { _trySetTitle(impl->ptr(), title); }
    m_build_config.m_title = title;
    return *this;
}

Window& This::setSize(Vec2i size) {
    if (impl && impl->window_exists) { _trySetSize(impl->ptr(), size.x, size.y); }
    m_build_config.m_size = size;
    return *this;
}

Window& This::setPosition(Vec2i position) {
    if (impl && impl->window_exists) { _trySetPos(impl->ptr(), position.x, position.y); }
    m_build_config.m_position = position;
    return *this;
}

Window& This::setAspectRatio(fp32 min, fp32 max) {
    if (impl && impl->window_exists) { _trySetAspectRatio(impl->ptr(), min, max); }
    m_build_config.m_aspect_ratio_min_max = {min, max};
    return *this;
}


Window& This::setResizable(bool yes) {
    if (impl && impl->window_exists) { _trySetResizable(impl->ptr(), yes); }
    m_build_config.m_is_resizable = yes;
    return *this;
}

Window& This::setMaximized(bool yes) {
    if (impl && impl->window_exists) {
        (yes)?
            (SDL_MaximizeWindow(impl->ptr())) : (SDL_RestoreWindow(impl->ptr()));
    }
    m_build_config.m_is_maximized = yes;
    return *this;
}
// friend of setMaximized
Window& This::toggleMaximized() {
    this->setMaximized(!(_getActiveFlags(impl->ptr()) & SDL_WINDOW_MAXIMIZED));
    return *this;
}

Window& This::setMinimized(bool yes) {
    if (impl && impl->window_exists) { _trySetMinimized(impl->ptr(), yes); }
    m_build_config.m_is_minimized = yes;
    return *this;
}

Window& This::setFullScreen(bool yes) {
    if (impl && impl->window_exists) { _trySetFullscreen(impl->ptr(), yes); }
    m_build_config.m_is_fullscreen = yes;
    return *this;
}

Window& This::setBorderless(bool yes) {
    if (impl && impl->window_exists) { _trySetBorderless(impl->ptr(), yes); }
    m_build_config.m_is_borderless = yes;
    return *this;
}

Window& This::setHidden(bool yes) {
    if (impl && impl->window_exists) { _trySetHidden(impl->ptr(), yes); }
    m_build_config.m_is_hidden = yes;
    return *this;
}

Window& This::setAlwaysOnTop(bool yes) {
    if (impl && impl->window_exists) { _trySetAlwaysOnTop(impl->ptr(), yes); }
    m_build_config.m_is_always_on_top = yes;
    return *this;
}

Window& This::setKeyboardGrabbed(bool yes) {
    if (impl && impl->window_exists) { _trySetKeyboardGrabbed(impl->ptr(), yes); }
    m_build_config.m_is_keyboard_grabbed = yes;
    return *this;
}

Window& This::setMouseGrabbed(bool yes) {
    if (impl && impl->window_exists) { _trySetMouseGrabbed(impl->ptr(), yes); }
    m_build_config.m_is_mouse_grabbed = yes;
    return *this;
}

Window& This::setMouseRelative(bool yes) {
    if (impl && impl->window_exists) { _trySetMouseRelative(impl->ptr(), yes); }
    m_build_config.m_is_mouse_relative = yes;
    return *this;
}



NAMESPACE_END(vexa)
