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
public:
    struct M {
        bool is_loaded = false;
        void* image = nullptr;

        std::string_view path;
        Vec2i size;

    } m;

    Image() = default;
    Image(const Image&) = default;
    Image& operator= (const Image&) = default;
    Image(Image&&) = default;
    Image& operator= (Image&&) = default;
    //
    ~Image();


    // Load and return a image from path
    static Image Load(std::string_view path);

    // returns `true` if image was unloaded
    // returns `false` if it already was unloaded or didnt ever get loaded
    static bool Unload(RefMut<Image> image_ref);

    Vec2i size();
    std::string_view path();
};


NAMESPACE_END(vexa)
