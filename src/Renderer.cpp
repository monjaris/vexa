#include "vexa/Renderer.hpp"
#include "vexa/renderer_backend/gfx.hpp"
NAMESPACE_BEGIN(vexa)


#define FN "Renderer::{}(): "


/*
 * I used a little ambigious and unusual naming here(for shorter names):
 * m - message,  f - fatal, e - error  (before first underscore)
 */
IGNORE_WARNING_BEGIN("-Wunused-const-variable")
#define DEF_MSG static constexpr inline const char* const
    DEF_MSG mf_failed_to_create_renderer
        { "an error occured while creating the renderer" };

    DEF_MSG mf_renderer_never_existed_before
        { "invalid call on a renderer that has never been created" };

    DEF_MSG mf_renderer_currently_doesnt_exist
        { "invalid call on an already destroyed renderer" };

    DEF_MSG me_couldnt_create_renderer_already_exists
        { "couldn't create renderer because it already exists" };

#undef DEF_MSG
IGNORE_WARNING_END("-Wunused-const-variable")



using This = Renderer;


class This::Impl {
    friend class Renderer;
    bool m_renderer_exists = false;
    bool m_renderer_ever_existed = false;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;

public:
    explicit Impl() = default;

    ~Impl() {
        if (m_renderer_exists) {
            SDL_DestroyRenderer(m_renderer);
            m_window = nullptr;
            m_renderer_exists = false;
        }
    }
};

// Ctor
This::Renderer(This::Cfg config): impl(new Impl{}), m_build_config(config) {}
// Dtor
This::~Renderer() {};

This::Renderer(Renderer&& other) noexcept
    : impl(std::move(other.impl))
{
    other.impl = nullptr;
    m_build_config = other.m_build_config;
}

Renderer& This::operator= (Renderer&& other) noexcept {
    if (this != &other) {
        if (impl == nullptr) {
            // this->~Renderer();
        }
        impl = std::move(other.impl);  other.impl = nullptr;
        m_build_config = other.m_build_config;
    }
    return *this;
}


Renderer This::create(void* window_ptr) {
    Renderer build = Renderer{};
    build.m_build_config = m_build_config;

    IF_THEN(impl->m_renderer_exists, log::error(FN"{}", __func__, me_couldnt_create_renderer_already_exists);)

    build.impl->m_window = (SDL_Window*)window_ptr;
    // try creating renderer, exit with message on fail
    build.impl->m_renderer = SDL_CreateRenderer(build.impl->m_window, nullptr);
    IF_THEN(!build.impl->m_renderer, log::fatal(FN"{}: {}", __func__, mf_failed_to_create_renderer,
        SDL_GetError());)

    // mark renderer is created
    build.impl->m_renderer_ever_existed = build.impl->m_renderer_exists = true;
    log::info(FN"created renderer for window [ID={}]",
        __func__, SDL_GetWindowID((SDL_Window*)window_ptr)
    );

    return build;
}

void This::destroy() {
    impl->m_renderer_exists = false;
    impl = nullptr;
    m_build_config.reset();
}

bool This::exists() {
    return impl->m_renderer_exists;
}




Renderer& This::setVsync(bool enabled) {
    m_build_config.vsync = enabled;
    return *this;
}


void This::start() {
    SDL_RenderClear(impl->m_renderer);
}
// overload for clearing with Color8
void This::start(ColorU8 color) {
    gfx::set_rgba_u8(impl->m_renderer, color);
    SDL_RenderClear(impl->m_renderer);
}
// overload for clearing with Color8
void This::start(ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    SDL_RenderClear(impl->m_renderer);
}

void This::finish() {
    SDL_RenderPresent(impl->m_renderer);
}




void This::triangleFill(Triangle triangle, ColorU8 color) {
    gfx::set_rgba_f32(impl->m_renderer, color.toF32());
    gfx::fill_triangle_rgbaF32(impl->m_renderer, triangle);
}

void This::triangleFill(Triangle triangle, ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    gfx::fill_triangle_rgbaF32(impl->m_renderer, triangle);
}

void This::triangleLines(Triangle triangle, ColorU8 color) {
    
}

void This::triangleLines(Triangle triangle, ColorF32 color) {
    
}



void This::rectFill(Rect rectangle, ColorU8 color) {
    gfx::set_rgba_u8(impl->m_renderer, color);
    gfx::fill_rectangle(impl->m_renderer, rectangle);
}
void This::rectFill(Rect rectangle, ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    gfx::fill_rectangle(impl->m_renderer, rectangle);
}

void This::rectLines(Rect rectangle, ColorU8 color) {
    gfx::set_rgba_u8(impl->m_renderer, color);
    gfx::line_rectangle(impl->m_renderer, rectangle);
}
void This::rectLines(Rect rectangle, ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    gfx::line_rectangle(impl->m_renderer, rectangle);
}

template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], ColorU8 color) {
    gfx::set_rgba_u8(impl->m_renderer, color);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}

template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], ColorU8 color) {
    gfx::set_rgba_u8(impl->m_renderer, color);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rgba_f32(impl->m_renderer, color);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}


NAMESPACE_END(vexa)
