#include "vexa/core/defs.hpp"
NAMESPACE_BEGIN(vexa::gfx)



// sets implementation-side global color variable and internal renderer color to a value
// eg. for triangle its global variable and for rectangle its SDL's color setter
bool set_triangle_color32(fp32 r, fp32 g, fp32 b, fp32 a);
bool set_rectangle_color32(fp32 r, fp32 g, fp32 b, fp32 a);
bool set_rectangle_color8(uint8 r, uint8 g, uint8 b, uint8 a);
bool set_circle_color32(fp32 r, fp32 g, fp32 b, fp32 a);
//
bool set_brush_color32(SDL_Renderer* renderer_ptr, fp32 r, fp32 g, fp32 b, fp32 a);
bool set_brush_color8(SDL_Renderer* renderer_ptr, uint8 r, uint8 g, uint8 b, uint8 a);



//
void line_thin(void* renderer_ptr, fp32 x1, fp32 y1, fp32 x2, fp32 y2);
//
void line_wide(void* renderer_ptr, fp32 x1, fp32 y1, fp32 x2, fp32 y2, uint32 w);


//
void fill_triangle(void* renderer_ptr, fp32 ax, fp32 ay, fp32 bx, fp32 by, fp32 cx, fp32 cy);
//
void line_triangle_rgba32(void* renderer_ptr, fp32 a, fp32 b, fp32 c);
//
template<usize N> inline void fill_N_triangle_rgba32(
    void*renderer_ptr, fp32 (&a)[N], fp32 (&b)[N], fp32 (&c)[N]
);
//
template<usize N> inline void line_N_triangle_rgba32(
    void* renderer_ptr, fp32 (&a)[N], fp32 (&b)[N], fp32 (&c)[N]
);


//
void fill_rectangle(void* renderer_ptr, fp32 x, fp32 y, fp32 w, fp32 h);
//
void line_rectangle(void* renderer_ptr, fp32 x, fp32 y, fp32 w, fp32 h);
//
template<usize N> void fill_N_rectangle(
    void* renderer_ptr, fp32 (&x)[N], fp32 (&y)[N], fp32 (&w)[N], fp32 (&h)[N]
);
//
template<usize N> void line_N_rectangle(
    void* renderer_ptr, fp32 (&x)[N], fp32 (&y)[N], fp32 (&w)[N], fp32 (&h)[N]
);



constexpr uint32 MAX_SEGMENTS = 128;
//
void fill_circle(void* renderer_ptr, fp32 x, fp32 y, fp32 r, uint32 segments);
//
void line_circle(void* renderer_ptr, fp32 x, fp32 y, fp32 r, const uint32 quality);
//
template<usize N>
void fill_N_circle(void* renderer_ptr, fp32 x, fp32 y, fp32 r, const uint32 quality);
//
template<usize N>
void line_N_circle(void* renderer_ptr, fp32 x, fp32 y, fp32 r, const uint32 quality);



NAMESPACE_END(vexa::gfx)
