#include "vexa/alt/SDL3.h"
#include "vexa/core/common.hpp"
NAMESPACE_BEGIN(vexa::gfx)

#define SDL_REND() ((SDL_Renderer*)sdl_renderer)



constexpr inline bool set_rgba_u8(void* sdl_renderer, ColorU8 color);
constexpr inline bool set_rgba_f32(void* sdl_renderer, ColorF32 color);


void line_xy(void* sdl_renderer, Vec2 pos1, Vec2 pos2) {
    
}
void line_xy_w(void* sdl_renderer, Vec2 pos1, Vec2 pos2, uint32 thickness) {
    
}


void fill_triangle_rgbaF32(void* sdl_renderer, Triangle triangle);
void line_triangle_rgbaF32(void* sdl_renderer, Triangle triangle);
template<usize N> inline void fill_N_triangle_rgbaF32(Triangle (&triangle_array)[N], ColorF32 color) {
    
}
template<usize N> inline void line_N_triangle_rgbaF32(Triangle (&triangle_array)[N], ColorF32 color) {
    
}



void fill_rectangle(void* sdl_renderer, Rect rect);
void line_rectangle(void* sdl_renderer, Rect rect);
template<usize N> void fill_N_rectangle(void* sdl_renderer, Rect (&rectangle_array)[N]);
template<usize N> void line_N_rectangle(void* sdl_renderer, Rect (&rectangle_array)[N]);




void fill_circle(void* sdl_renderer, Circle<> circle);
void line_circle(void* sdl_renderer, Circle<> circle);
template<usize N> void fill_circle(void* sdl_renderer, Circle<> circle);
template<usize N> void fill_circle(void* sdl_renderer, Circle<> circle);



NAMESPACE_END(vexa::gfx)
