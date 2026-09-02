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



This::Renderer(This::Cfg config): impl(new Impl{}), m_build_config(config) {}

This::~Renderer() = default;

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
    Renderer build = {};
    build.m_build_config = m_build_config;

    IF_THEN(impl->m_renderer_exists, log::error(FN"{}", __func__, me_couldnt_create_renderer_already_exists);)

    build.impl->m_window = (SDL_Window*)window_ptr;
    // try creating renderer, exit with message on fail
    build.impl->m_renderer = SDL_CreateRenderer(build.impl->m_window, nullptr);
    IF_THEN(!build.impl->m_renderer, log::fatal(FN"{}: {}", __func__, mf_failed_to_create_renderer,
        SDL_GetError());)

    // mark renderer is created
    build.impl->m_renderer_ever_existed = build.impl->m_renderer_exists = true;
    log::info(FN"created new renderer for window [ID={}]",
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

bool This::getVsync() {
    return m_build_config.vsync;
}


void This::start() {
    gfx::set_brush_color8(impl->m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(impl->m_renderer);
}
//
void This::start(void* null) {
    SDL_RenderClear(impl->m_renderer);
}
// overload for clearing with Color8
void This::start(ColorU8 color) {
    gfx::set_brush_color8(impl->m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(impl->m_renderer);
}
// overload for clearing with Color8
void This::start(ColorF32 color) {
    gfx::set_brush_color32(impl->m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(impl->m_renderer);
}

void This::finish() {
    SDL_RenderPresent(impl->m_renderer);
}



Texture This::loadTexture(Image texture_source) {
    return Texture::M_Load(impl->m_renderer, texture_source);
}
// overload
Texture This::loadTexture(const char* texture_source_path) {
    return loadTexture(Image::Load(texture_source_path));
}


void This::renderTexture(
    const Texture& texture, Vec2 pos
)
{
    SDL_FRect dest = {
        pos.x, pos.y,
        CAST<fp32>(CAST<SDL_Texture*>(texture.m.texture)->w),
        CAST<fp32>(CAST<SDL_Texture*>(texture.m.texture)->h)
    };

    SDL_RenderTexture(
        impl->m_renderer, CAST<SDL_Texture*>(texture.m.texture),
        nullptr, &dest
    );
}
// overload
void This::renderTexture(
    const Texture& texture, Rect src, Rect dest
)
{
    SDL_FRect src_rect = {src.pos.x, src.pos.x, src.size.y, src.size.y};
    SDL_FRect dest_rect = {dest.pos.x, dest.pos.x, dest.size.y, dest.size.y};

    SDL_RenderTexture(
        impl->m_renderer, CAST<SDL_Texture*>(texture.m.texture),
        src.isEmpty()? nullptr : &src_rect,
        dest.isEmpty()? nullptr : &dest_rect
    );
}
// overload again
void This::renderTexture(
    const Texture& texture, Rect dest
)
{
    SDL_FRect dest_rect = {dest.pos.x, dest.pos.x, dest.size.y, dest.size.y};

    SDL_RenderTexture(
        impl->m_renderer, CAST<SDL_Texture*>(texture.m.texture),
        nullptr, &dest_rect
    );
}



void This::triangleFill(Triangle triangle, ColorU8 color) {
    ColorF32 color_f32 = color.toF32();
    gfx::set_triangle_color32(color_f32.r, color_f32.g, color_f32.b, color_f32.a);
    gfx::fill_triangle(impl->m_renderer,
        triangle.first.x, triangle.first.y,
        triangle.middle.x, triangle.middle.y,
        triangle.last.x, triangle.last.y
    );
}

void This::triangleFill(Triangle triangle, ColorF32 color) {
    gfx::set_triangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_triangle(impl->m_renderer,
        triangle.first.x, triangle.first.y,
        triangle.middle.x, triangle.middle.y,
        triangle.last.x, triangle.last.y
    );
}

void This::triangleLines(Triangle triangle, ColorU8 color) {
    
}

void This::triangleLines(Triangle triangle, ColorF32 color) {
    
}



void This::rectFill(Rect rectangle, ColorU8 color) {
    gfx::set_rectangle_color8(color.r, color.g, color.b, color.a);
    gfx::fill_rectangle(impl->m_renderer,
        rectangle.pos.x, rectangle.pos.y,
        rectangle.size.x, rectangle.size.y
    );
}
void This::rectFill(Rect rectangle, ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_rectangle(impl->m_renderer,
        rectangle.pos.x, rectangle.pos.y,
        rectangle.size.x, rectangle.size.y
    );
}

void This::rectLines(Rect rectangle, ColorU8 color) {
    gfx::set_rectangle_color8(color.r, color.g, color.b, color.a);
    gfx::line_rectangle(impl->m_renderer,
        rectangle.pos.x, rectangle.pos.y,
        rectangle.size.x, rectangle.size.y
    );
}
void This::rectLines(Rect rectangle, ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::line_rectangle(impl->m_renderer,
        rectangle.pos.x, rectangle.pos.y,
        rectangle.size.x, rectangle.size.y
    );
}

template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], ColorU8 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}

template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], ColorU8 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}




void This::PolyFill(Vec2 pos, Vec2 size, ColorU8 color) {
    
}

void This::PolyLines(Vec2 pos, Vec2 size, ColorU8 color) {
    
}



void This::circleFill(Circle circle, ColorU8 color, fp32 quality) {
    ColorF32 color_f32 = color.toF32();
    gfx::set_circle_color32(color_f32.r, color_f32.g, color_f32.b, color_f32.a);
    gfx::fill_circle(impl->m_renderer,
        circle.pos.x, circle.pos.y, circle.radius,
        circle.segments(quality)
    );
}

void This::circleFill(Circle circle, ColorF32 color, fp32 quality) {
    gfx::set_circle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_circle(impl->m_renderer,
        circle.pos.x, circle.pos.y, circle.radius,
        circle.segments(quality)
    );
}

void This::circleLines(Circle circle, ColorU8 color) {
    
}

void This::circleLines(Circle circle, ColorF32 color) {
    
}





NAMESPACE_END(vexa)
