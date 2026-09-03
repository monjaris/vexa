#include "vexa/alt/SDL3.h"
#include "vexa/renderer_backend/gfx.hpp"
#include <algorithm>
#include <span>

// forward declare so we can use them without including <cmath>
extern "C" { float cosf(float);  float sinf(float); }
// also lets put math::'s PI32 here instead of including a header
constexpr vexa::fp32 PI32 = 3.14159265f;


NAMESPACE_BEGIN(vexa)

#define SDL_REND ((SDL_Renderer*)renderer_ptr)


namespace global_state {
    fp32 rect_rgba[4];
    fp32 triangle_rgba[4];
    fp32 circle_rgba[4];
}
namespace g = global_state;

//
bool gfx::set_triangle_color32(fp32 r, fp32 g, fp32 b, fp32 a) {
    g::triangle_rgba[0] = r; g::triangle_rgba[1] = g;
    g::triangle_rgba[2] = b; g::triangle_rgba[3] = a;
    return true;
}
//
bool gfx::set_rectangle_color32(fp32 r, fp32 g, fp32 b, fp32 a) {
    g::rect_rgba[0] = r; g::rect_rgba[1] = g;
    g::rect_rgba[2] = b; g::rect_rgba[3] = a;
    return true;
}
bool gfx::set_rectangle_color8(uint8 r, uint8 g, uint8 b, uint8 a) {
    g::rect_rgba[0] = r; g::rect_rgba[1] = g;
    g::rect_rgba[2] = b; g::rect_rgba[3] = a;
    return true;
}
//
bool gfx::set_circle_color32(fp32 r, fp32 g, fp32 b, fp32 a) {
    g::circle_rgba[0] = r; g::circle_rgba[1] = g;
    g::circle_rgba[2] = b; g::circle_rgba[3] = a;
    return true;
}
//
bool gfx::set_brush_color32(
    SDL_Renderer* renderer_ptr, fp32 r, fp32 g, fp32 b, fp32 a
){
    return SDL_SetRenderDrawColorFloat(SDL_REND, r, g, b, a);
}
bool gfx::set_brush_color8(
    SDL_Renderer* renderer_ptr, uint8 r, uint8 g, uint8 b, uint8 a
){
    return SDL_SetRenderDrawColor(SDL_REND, r, g, b, a);
}





//
void gfx::line_thin(void* renderer_ptr, fp32 x1, fp32 y1, fp32 x2, fp32 y2) {
    SDL_RenderLine(SDL_REND, x1, y1, x2, y2);
}


//
void gfx::line_wide(void* renderer_ptr, fp32 x1, fp32 y1, fp32 x2, fp32 y2, uint32 w) {
    
}


//
void gfx::fill_triangle(
    void* renderer_ptr, fp32 ax,fp32 ay, fp32 bx,fp32 by, fp32 cx,fp32 cy
){
    auto& clr = g::triangle_rgba;

    const SDL_Vertex vertices[3] = {
        SDL_Vertex {
            .position = {ax, ay},
            .color = {clr[0], clr[1], clr[2], clr[3]},
            .tex_coord = {0.0f, 0.0f},
        },
        SDL_Vertex {
            .position = {bx, by},
            .color = {clr[0], clr[1], clr[2], clr[3]},
            .tex_coord = {0.0f, 0.0f},
        },
        SDL_Vertex {
            .position = {cx, cy},
            .color = {clr[0], clr[1], clr[2], clr[3]},
            .tex_coord = {0.0f, 0.0f},
        }
    };

    SDL_RenderGeometry(SDL_REND, nullptr, vertices, 3, nullptr, 0);
}


//
void gfx::line_triangle_rgba32(void* renderer_ptr, fp32 a, fp32 b, fp32 c) {
    ;
}


//
template<usize N> inline
void gfx::fill_N_triangle_rgba32(
    void* renderer_ptr,
    fp32 (&a)[N],
    fp32 (&b)[N],
    fp32 (&c)[N]
) {

}


//
template<usize N> inline
void gfx::line_N_triangle_rgba32(
    void* renderer_ptr,
    fp32 (&a)[N],
    fp32 (&b)[N],
    fp32 (&c)[N]
) {

}


//
void gfx::fill_rectangle(void* renderer_ptr, fp32 x, fp32 y, fp32 w, fp32 h) {
    SDL_SetRenderDrawColorFloat(SDL_REND,
        g::rect_rgba[0], g::rect_rgba[1], g::rect_rgba[2], g::rect_rgba[3]
    );
    const SDL_FRect sdl_rect = {x, y, w, h};
    SDL_RenderFillRect(SDL_REND, &sdl_rect);
}


//
void gfx::line_rectangle(
    void* renderer_ptr,
    fp32 x,
    fp32 y,
    fp32 w,
    fp32 h
) {
    const SDL_FRect sdl_rect = {x, y, w, h};
    SDL_RenderRect(SDL_REND, &sdl_rect);
}


//
template<usize N> inline
void gfx::fill_N_rectangle(
    void* renderer_ptr,
    fp32 (&x)[N],
    fp32 (&y)[N],
    fp32 (&w)[N],
    fp32 (&h)[N]
) {
    // SDL_RenderFillRects needs an SDL_FRect array,
    // so these scalar arrays need to be packed first.
}




//
template<usize N> inline
void gfx::line_N_rectangle(
    void* renderer_ptr,
    fp32 (&x)[N],
    fp32 (&y)[N],
    fp32 (&w)[N],
    fp32 (&h)[N]
) {
    
}


//
// template<fp32 t_quality>
// void gfx::fill_circle(
//     void* renderer_ptr,
//     fp32 x, fp32 y, fp32 r
// )
// {
//     auto& clr = g::circle_rgba;

    

//     uint32 segments = t_quality * (2.0f * PI32 * r);
//     SDL_Vertex vertices[t_quality * 300];
//     int32 indices[t_quality * 900 + 1];

//     fp32 step_rad = 2.0f * PI32 / segments;

//     vertices[0] = {
//         .position = {x, y},
//         .color = {clr[0], clr[1], clr[2], clr[3]},
//         .tex_coord = {0.0f, 0.0f}
//     };

//     for (uint64 i = 0; i < segments; ++i) {
//         fp32 angle = step_rad * i;

//         fp32 x_i = x + ::cosf(angle) * r;
//         fp32 y_i = y + ::sinf(angle) * r;

//         vertices[i + 1] = {
//             .position = {x_i, y_i},
//             .color = {clr[0], clr[1], clr[2], clr[3]},
//             .tex_coord = {0.0f, 0.0f}
//         };

//         uint32 current = i + 1;
//         uint32 next = current % segments + 1;

//         indices[i * 3 + 0] = 0;
//         indices[i * 3 + 1] = current;
//         indices[i * 3 + 2] = next;
//     }

//     SDL_RenderGeometry(
//         SDL_REND,
//         nullptr,
//         vertices,
//         segments + 1,
//         indices,
//         segments * 3
//     );
// }







void gfx::fill_circle(void* renderer_ptr, fp32 x, fp32 y, fp32 r, uint32 segments) {
    auto& clr = g::circle_rgba;

    segments = (segments > MAX_SEGMENTS) ? MAX_SEGMENTS : segments;
    segments = (segments < 3) ? 3 : segments;

    SDL_Vertex vertices[MAX_SEGMENTS + 1];
    int32 indices [MAX_SEGMENTS * 3];

    fp32 step_rad = 2.0f * PI32 / CAST<fp32>(segments);

    vertices[0] = {
        .position  = {x, y},
        .color     = {clr[0], clr[1], clr[2], clr[3]},
        .tex_coord = {0.0f, 0.0f}
    };

    for (uint32 i = 0; i < segments; ++i)
    {
        fp32 angle = step_rad * static_cast<fp32>(i);

        fp32 x_i = x + ::cosf(angle) * r;
        fp32 y_i = y + ::sinf(angle) * r;

        vertices[i + 1] = {
            .position  = {x_i, y_i},
            .color     = {clr[0], clr[1], clr[2], clr[3]},
            .tex_coord = {0.0f, 0.0f}
        };

        uint32 current = i + 1;
        uint32 next    = (current % segments) + 1;

        indices[i * 3 + 0] = 0;
        indices[i * 3 + 1] = CAST<int32>(current);
        indices[i * 3 + 2] = CAST<int32>(next);
    }

    SDL_RenderGeometry(
        SDL_REND,
        nullptr,
        vertices,
        CAST<int>(segments + 1),
        indices,
        CAST<int>(segments * 3)
    );
}





//
void gfx::line_circle(
    void* renderer_ptr,
    fp32 x,
    fp32 y,
    fp32 r,
    const uint32 quality
) {

}


//
template<usize N>
void gfx::fill_N_circle(
    void* renderer_ptr,
    fp32 x,
    fp32 y,
    fp32 r,
    const uint32 quality
) {

}


//
template<usize N>
void gfx::line_N_circle(
    void* renderer_ptr,
    fp32 x,
    fp32 y,
    fp32 r,
    const uint32 quality
) {

}


NAMESPACE_END(vexa)
