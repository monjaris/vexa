#include "vexa/alt/SDL3.h"
#include "vexa/core/common.hpp"
NAMESPACE_BEGIN(vexa::gfx)

#define SDL_REND() ((SDL_Renderer*)sdl_renderer)


namespace detail {
    ColorF32 rgba_f32_triangle = {0, 0, 0};
}
namespace det = detail;


constexpr inline bool set_rgba_u8(void* sdl_renderer, ColorU8 color) {
    return SDL_SetRenderDrawColor(SDL_REND(), color.r, color.g, color.b, color.a);
}

constexpr inline bool set_rgba_f32(void* sdl_renderer, ColorF32 color) {
    det::rgba_f32_triangle = {color.r, color.g, color.b, color.a};
    return SDL_SetRenderDrawColorFloat(SDL_REND(), color.r, color.g, color.b, color.a);
}



void line_xy(void* sdl_renderer, Vec2f pos1, Vec2f pos2) {
    
}

void line_xy_w(void* sdl_renderer, Vec2f pos1, Vec2f pos2, uint32 thickness) {
    
}




void fill_triangle_rgbaF32(void* sdl_renderer, Triangle triangle) {
    auto& clr = det::rgba_f32_triangle;

    const SDL_Vertex vertices[3] = {
        SDL_Vertex {
            .position = {triangle.first.x, triangle.first.y},
            .color = {clr.r, clr.g, clr.b, clr.a},
            .tex_coord = {0.0, 0.0},
        },
        SDL_Vertex {
            .position = {triangle.middle.x, triangle.middle.y},
            .color = {clr.r, clr.g, clr.b, clr.a},
            .tex_coord = {0.0, 0.0},
        },
        SDL_Vertex {
            .position = {triangle.last.x, triangle.last.y},
            .color = {clr.r, clr.g, clr.b, clr.a},
            .tex_coord = {0.0, 0.0},
        }
    };

    SDL_RenderGeometry(SDL_REND(), nullptr, vertices, 3, nullptr, 0);
}

void line_triangle_rgbaF32(void* sdl_renderer, Triangle triangle) {
    auto& clr = det::rgba_f32_triangle;
}


template<usize N> inline void fill_N_triangle_rgbaF32(Triangle (&triangle_array)[N], ColorF32 color) {
    
}


template<usize N> inline void line_N_triangle_rgbaF32(Triangle (&triangle_array)[N], ColorF32 color) {
    
}




inline void fill_rectangle(void* sdl_renderer, Rect rect) {
    const SDL_FRect sdl_rect = {rect.pos.x, rect.pos.y, rect.size.x, rect.size.y};
    SDL_RenderFillRect(SDL_REND(), &sdl_rect);
}


void line_rectangle(void* sdl_renderer, Rect rect) {
    const SDL_FRect sdl_rect = {rect.size.x, rect.size.y, rect.pos.x, rect.pos.y};
    SDL_RenderRect(SDL_REND(), &sdl_rect);
}


template<usize N> void fill_N_rectangle(void* sdl_renderer, Rect (&rectangle_array)[N]) {
    SDL_RenderFillRects(SDL_REND(), rectangle_array, N);
}


template<usize N> void line_N_rectangle(void* sdl_renderer, Rect (&rectangle_array)[N]) {
    SDL_RenderRects(SDL_REND(), rectangle_array, N);
}




NAMESPACE_END(vexa::gfx)
