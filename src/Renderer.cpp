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
    bool m_init = false;
    bool m_renderer_ever_existed = false;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;

public:
    explicit Impl() = default;

    ~Impl() {
        if (m_init) {
            log::info("Renderer::destroy(): destroyed renderer of window [ID={}]",
                SDL_GetWindowID(m_window)
            );
            SDL_DestroyRenderer(m_renderer);
            m_window = nullptr;
            m_init = false;
        }
    }
};



This::Renderer(This::Cfg config): impl(new Impl{}), m_bconfig(config) {}

This::~Renderer() = default;

This::Renderer(Renderer&& other) noexcept
    : impl(std::move(other.impl))
{
    other.impl = nullptr;
    m_bconfig = other.m_bconfig;
}

Renderer& This::operator= (Renderer&& other) noexcept {
    if (this != &other) {
        if (impl == nullptr) {
            // this->~Renderer();
        }
        impl = std::move(other.impl);  other.impl = nullptr;
        m_bconfig = other.m_bconfig;
    }
    return *this;
}


Renderer This::create(void* window_ptr) {
    Renderer build = {};
    build.m_bconfig = m_bconfig;

    IF_THEN(impl->m_init, log::error(FN"{}", __func__, me_couldnt_create_renderer_already_exists);)

    build.impl->m_window = (SDL_Window*)window_ptr;
    // try creating renderer, exit with message on fail
    build.impl->m_renderer = SDL_CreateRenderer(build.impl->m_window, nullptr);
    IF_THEN(!build.impl->m_renderer, log::fatal(FN"{}: {}", __func__, mf_failed_to_create_renderer,
        SDL_GetError());)

    // mark renderer is created
    build.impl->m_renderer_ever_existed = build.impl->m_init = true;
    log::info(FN"created new renderer for window [ID={}]",
        __func__, SDL_GetWindowID((SDL_Window*)window_ptr)
    );

    return build;
}

void This::destroy() {
    log::info("Renderer::destroy(): destroyed renderer of window [ID={}]",
        SDL_GetWindowID(impl->m_window)
    );
    impl->m_init = false;
    impl.reset();
    m_bconfig.reset();
}

bool This::exists() {
    return impl->m_init;
}




Renderer& This::setVsync(bool enabled) {
    m_bconfig.vsync = enabled;
    if (impl->m_init) {
        SDL_SetRenderVSync(impl->m_renderer, enabled);
    }
    return *this;
}

bool This::vsync() {
    int vsync;
    SDL_GetWindowSurfaceVSync(impl->m_window, &vsync);
    return vsync;
}

void This::setMode(Mode render_mode) {
    m_bconfig.mode = CAST<uint8>(render_mode);
    if (impl->m_init) {
        int win_w, win_h;
        SDL_GetWindowSize(impl->m_window, &win_w, &win_h);
        SDL_SetRenderLogicalPresentation(
            impl->m_renderer, win_w, win_h, SDL_RendererLogicalPresentation(CAST<uint8>(render_mode))
        );
    }
}

This::Mode This::mode() {
    int win_w, win_h;
    SDL_RendererLogicalPresentation rlp;

    SDL_GetWindowSize(impl->m_window, &win_w, &win_h);
    SDL_GetRenderLogicalPresentation(impl->m_renderer, &win_w, &win_h, &rlp);

    return CAST<Mode>(rlp);
}




void This::start() {
    gfx::set_brush_color8(impl->m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(impl->m_renderer);
}
//
void This::start(nullptrT) {
    SDL_RenderClear(impl->m_renderer);
}
// overload for clearing with Color8
void This::start(Color color) {
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



Texture This::loadTexture(Image&& texture_source) noexcept {
    return Texture::M_Load(impl->m_renderer, texture_source);
}
// overload
Texture This::loadTexture(Font& font, uint64 font_size, const char* text) noexcept {
    font.setSize(font_size);
    Image image = font.createImage(text, Color::BLACK, Color::WHITE);
    return loadTexture(std::move(image));
}



// render texture at given pos
void This::drawTexture(const Texture& texture, Vec2 pos)
{
    auto* sdl_texture = CAST<SDL_Texture*>(texture.m.texture);

    SDL_FRect dest = {
        pos.x, pos.y,
        CAST<fp32>(sdl_texture->w),
        CAST<fp32>(sdl_texture->h)
    };

    SDL_RenderTexture(impl->m_renderer, sdl_texture, nullptr, &dest);
}
// overload
void This::drawTexture(const Texture& texture, Vec2 pos, Color color)
{
    SDL_SetTextureColorMod(CAST<SDL_Texture*>(texture.m.texture), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(CAST<SDL_Texture*>(texture.m.texture), color.a);
    drawTexture(texture, pos);
}
// overload again
void This::drawTexture(const Texture& texture, Rect src, Rect dest)
{
    SDL_FRect src_rect = {src.pos.x, src.pos.x, src.size.y, src.size.y};
    SDL_FRect dest_rect = {dest.pos.x, dest.pos.x, dest.size.y, dest.size.y};

    SDL_RenderTexture(
        impl->m_renderer, CAST<SDL_Texture*>(texture.m.texture),
        src.isEmpty()? nullptr : &src_rect,
        dest.isEmpty()? nullptr : &dest_rect
    );
}
// and again
void This::drawTexture(
    const Texture& texture, Rect src, Rect dest, Color color
){
    SDL_SetTextureColorMod(CAST<SDL_Texture*>(texture.m.texture), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(CAST<SDL_Texture*>(texture.m.texture), color.a);
    drawTexture(texture, src, dest);
}



// render font with text
void This::drawText(Font& font, const char* text, Vec2 pos, Color color) {
    static const char* previous = nullptr;
    if (previous != nullptr && previous == text) return;
    previous = text;
    Image image = font.createImage(text, Color::TRANSPARENT, color);
    Texture texture = loadTexture(std::move(image));
    drawTexture(texture, pos, color);
}



//  SHAPE RENDERING METHODS //

// render a `triangle` with `color`
void This::triangleFill(Triangle triangle, Color color) {
    ColorF32 color_f32 = color.toF32();
    gfx::set_triangle_color32(color_f32.r, color_f32.g, color_f32.b, color_f32.a);
    gfx::fill_triangle(impl->m_renderer,
        triangle.first.x, triangle.first.y,
        triangle.middle.x, triangle.middle.y,
        triangle.last.x, triangle.last.y
    );
}

// render a `triangle` with `color`
void This::triangleFill(Triangle triangle, ColorF32 color) {
    gfx::set_triangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_triangle(impl->m_renderer,
        triangle.first.x, triangle.first.y,
        triangle.middle.x, triangle.middle.y,
        triangle.last.x, triangle.last.y
    );
}

void This::triangleLines(Triangle triangle, Color color) {
    
}

void This::triangleLines(Triangle triangle, ColorF32 color) {
    
}



void This::rectFill(Rect rectangle, Color color) {
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

void This::rectLines(Rect rectangle, Color color) {
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

template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], Color color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectFillN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::fill_N_rectangle(impl->m_renderer, rectangle_array);
}

template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], Color color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}
template<usize N> void This::rectLinesN(Rect (&rectangle_array)[N], ColorF32 color) {
    gfx::set_rectangle_color32(color.r, color.g, color.b, color.a);
    gfx::line_N_rectangle(impl->m_renderer, rectangle_array);
}




void This::PolyFill(Vec2 pos, Vec2 size, Color color) {
    
}

void This::PolyLines(Vec2 pos, Vec2 size, Color color) {
    
}



void This::circleFill(Circle circle, Color color, fp32 quality) {
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

void This::circleLines(Circle circle, Color color) {
    
}

void This::circleLines(Circle circle, ColorF32 color) {
    
}





NAMESPACE_END(vexa)
