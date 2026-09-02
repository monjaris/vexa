#pragma once
#include <string_view>
#include "core/vec.hpp"
#include "core/common.hpp"
NAMESPACE_BEGIN(vexa)


/* TODO */
// SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
// SDL_PixelFormat format;     /**< The format of the surface, read-only */
// int w;                      /**< The width of the surface, read-only. */
// int h;                      /**< The height of the surface, read-only. */
// int pitch;                  /**< The distance in bytes between rows of pixels, read-only */
// void *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */
// int refcount;               /**< Application reference count, used when freeing surface */


class Image
{
    friend class Window;

    struct M {
        bool is_loaded = false;
        void* image = nullptr;
        const char* path;
    } m;


public:
    Image() = default;
    Image(const Image&) = default;
    Image& operator= (const Image&) = default;
    Image(Image&&) = default;
    Image& operator= (Image&&) = default;
    //
    ~Image();


    // Load and return a image from path
    static Image Load(const char* path) noexcept;

    // returns `true` if image was unloaded
    // returns `false` if it already was unloaded or didnt ever get loaded
    static bool Unload(RefMut<Image> image_ref) noexcept;

    bool operator== (const Image& other) const noexcept;

    void* ptr();
    Vec2i size();
    const char* path();
};


NAMESPACE_END(vexa)
