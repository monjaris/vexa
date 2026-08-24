#include "alt/SDL3.h"
#include "../include/Renderer.hpp"
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



constexpr bool This::_setColorU8(ColorU8 color) {
    return SDL_SetRenderDrawColor(impl->m_renderer, color.r, color.g, color.b, color.a);
}

constexpr bool This::_setColorF32(ColorF32 color) {
    return SDL_SetRenderDrawColorFloat(impl->m_renderer, color.r, color.g, color.b, color.a);
}

void This::_line(Vec2f pos1, Vec2f pos2) {
    SDL_RenderLine(impl->m_renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}


void This::_triangleFill(Triangle triangle, ColorF32 color) {
    const SDL_Vertex vertices[3] = {
        SDL_Vertex {
            .position = {triangle.first.x, triangle.first.y},
            .color = {color.r, color.g, color.b, color.a},
            .tex_coord = {0.0, 0.0},
        },
        SDL_Vertex {
            .position = {triangle.middle.x, triangle.middle.y},
            .color = {color.r, color.g, color.b, color.a},
            .tex_coord = {0.0, 0.0},
        },
        SDL_Vertex {
            .position = {triangle.last.x, triangle.last.y},
            .color = {color.r, color.g, color.b, color.a},
            .tex_coord = {0.0, 0.0},
        }
    };

    SDL_RenderGeometry(impl->m_renderer,
        nullptr, vertices, 3, nullptr, 0
    );
}

void This::_triangleLines(Triangle triangle, ColorF32 color) {
    _setColorF32(color);

    SDL_FPoint points[4] = {
        {triangle.first.x, triangle.first.y},
        {triangle.middle.x, triangle.middle.y},
        {triangle.last.x, triangle.last.y},
        {triangle.first.x, triangle.first.y},
    };

    SDL_RenderLines(impl->m_renderer, points, 4);
}


void This::_rectFill(Rect<> rect) {
    const SDL_FRect sdl_rect = {rect.pos.x, rect.pos.y, rect.size.x, rect.size.y};
    SDL_RenderFillRect(impl->m_renderer, &sdl_rect);
}

void This::_rectLines(Rect<> rect) {
    const SDL_FRect sdl_rect = {rect.size.x, rect.size.y, rect.pos.x, rect.pos.y};
    SDL_RenderRect(impl->m_renderer, &sdl_rect);
}

template<usize N> void This::_rectFillN(Rect<> (&rectangle_array)[N]) {
    SDL_RenderFillRects(impl->m_renderer, rectangle_array, N);
}

template<usize N> void This::_rectLinesN(Rect<> (&rectangle_array)[N]) {
    SDL_RenderRects(impl->m_renderer, rectangle_array, N);
}



Renderer& This::setVsync(bool enabled) {
    m_build_config.vsync = enabled;
    return *this;
}


void This::start(ColorU8 color) {
    _setColorU8(color);
    SDL_RenderClear(impl->m_renderer);
}
// overload for float[4] color
void This::start(ColorF32 color) {
    _setColorF32(color);
    SDL_RenderClear(impl->m_renderer);
}

void This::finish() {
    SDL_RenderPresent(impl->m_renderer);
}




void This::triangleFill(Triangle triangle, ColorU8 color) {
    _triangleFill(triangle, color.toF32());
}

void This::triangleFill(Triangle triangle, ColorF32 color) {
    _triangleFill(triangle, color);
}

void This::triangleLines(Triangle triangle, ColorU8 color) {
    _triangleLines(triangle, color.toF32());
}

void This::triangleLines(Triangle triangle, ColorF32 color) {
    _triangleLines(triangle, color);
}



void This::rectFill(Rect<> rectangle, ColorU8 color) {
    _setColorU8(color); _rectFill(rectangle);
}
void This::rectFill(Rect<> rectangle, ColorF32 color) {
    _setColorF32(color); _rectFill(rectangle);
}

void This::rectLines(Rect<> rectangle, ColorU8 color) {
    _setColorU8(color); _rectLines(rectangle);
}
void This::rectLines(Rect<> rectangle, ColorF32 color) {
    _setColorF32(color); _rectLines(rectangle);
}

template<usize N> void This::rectFillN(Rect<> (&rectangle_array)[N], ColorU8 color) {
    _setColorU8(color); _rectFillN(rectangle_array);
}
template<usize N> void This::rectFillN(Rect<> (&rectangle_array)[N], ColorF32 color) {
    _setColorF32(color); _rectFillN(rectangle_array);
}

template<usize N> void This::rectLinesN(Rect<> (&rectangle_array)[N], ColorU8 color) {
    _setColorU8(color); _rectLinesN(rectangle_array);
}
template<usize N> void This::rectLinesN(Rect<> (&rectangle_array)[N], ColorF32 color) {
    _setColorF32(color); _rectLinesN(rectangle_array);
}


NAMESPACE_END(vexa)
