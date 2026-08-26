#include "vexa/alt/SDL3.h"
#include "vexa/core/common.hpp"
NAMESPACE_BEGIN(vexa::gfx)

#define SDL_REND() ((SDL_Renderer*)sdl_renderer)


namespace detail {
    ColorF32 rgba_f32_triangle = {0, 0, 0};
}
namespace det = detail;


bool set_rgba_u8(void* sdl_renderer, ColorU8 color) {
    return SDL_SetRenderDrawColor(SDL_REND(), color.r, color.g, color.b, color.a);
}

bool set_rgba_f32(void* sdl_renderer, ColorF32 color) {
    det::rgba_f32_triangle = {color.r, color.g, color.b, color.a};
    return SDL_SetRenderDrawColorFloat(SDL_REND(), color.r, color.g, color.b, color.a);
}



// void line_xy(void* sdl_renderer, Vec2f pos1, Vec2f pos2) {
    // 
// }

// void line_xy_w(void* sdl_renderer, Vec2f pos1, Vec2f pos2, uint32 thickness) {
    // 
// }




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




void fill_rectangle(void* sdl_renderer, Rect rect) {
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




void fill_circle(void* sdl_renderer, Circle circle) {
    SDL_Vertex vertices[Circle::SEGMENTS + 1];
    uint64 points[Circle::SEGMENTS * 3];

    auto& _color = det::rgba_f32_triangle;

    // set up center vertex
    vertices[0] = {
        .position = { circle.pos.x, circle.pos.y },
        .color = { .r = _color.r,  .g = _color.g,  .b = _color.b,  .a = _color.a },
        .tex_coord = { 0.0f, 0.0f }
    };

    for (uint32 i=0;  i < Circle::SEGMENTS*3;  ++i) {
        fp32 x = math::cos(circle.pos.x * i);
        fp32 y = math::sin(circle.pos.y * i);

        vertices[i + 1] = {
            .position = { x, y },
            .color = { .r = _color.r,  .g = _color.g,  .b = _color.b,  .a = _color.a },
            .tex_coord = { 0.0f, 0.0f }
        };
    }

    // for (uint32 i=0;  i < )
}




// Move segments to global scope as a constant compile-time integer
constexpr uint32_t SEGMENTS = 32;

void DrawCircle(SDL_Renderer* renderer, float centerX, float centerY, float radius, SDL_FColor color) {
    SDL_Vertex vertices[SEGMENTS+1];
    int indices[SEGMENTS*3];

    // -------------------------------------------------------------------------
    // 1. SET UP VERTICES (The points in 2D space)
    // -------------------------------------------------------------------------
    // Index 0 is the center point of the circle (shared by all pie slices)
    vertices[0] = {{centerX, centerY}, color, {0.5f, 0.5f}};

    // Calculate the slice angle step size in Radians.
    // Full circle = 2 * PI radians (360 degrees).
    constexpr float ANGLE_STEP = (2.0f * math::PI32) / static_cast<float>(SEGMENTS);

    for (uint32_t i = 0; i < SEGMENTS; ++i) {
        // Current angle for this segment
        float angle = static_cast<float>(i) * ANGLE_STEP;

        // Calculate (X, Y) offset using Cosine and Sine.
        // Google: "How cos and sin map coordinates on a circle"
        float x = centerX + (radius * std::cos(angle));
        float y = centerY + (radius * std::sin(angle));

        // Place perimeter vertex starting at array index 1
        vertices[i + 1] = {{x, y}, color, {0.0f, 0.0f}};
    }

    // -------------------------------------------------------------------------
    // 2. SET UP INDICES (Connecting points into triangles)
    // -------------------------------------------------------------------------
    // Fill indices without an external counter variable
    for (uint32_t i = 0; i < SEGMENTS; ++i) {
        uint32_t base = i * 3; // Position in the indices array for this triangle

        indices[base + 0] = 0;                          // Corner 1: Center point
        indices[base + 1] = i + 1;                      // Corner 2: Current outer point
        indices[base + 2] = (i == SEGMENTS - 1) ? 1 : (i + 2); // Corner 3: Next outer point (or wrap to 1)
    }

    // Pass stack pointers straight to GPU driver
    SDL_RenderGeometry(renderer, nullptr, vertices, SEGMENTS+1, indices, SEGMENTS*3);
}




void line_circle(void* sdl_renderer, Circle<> circle);
template<usize N> void fill_circle(void* sdl_renderer, Circle<> circle);
template<usize N> void fill_circle(void* sdl_renderer, Circle<> circle);



NAMESPACE_END(vexa::gfx)
