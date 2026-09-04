#pragma once
#include <string_view>
#include "core/vec.hpp"
#include "core/memory.hpp"
NAMESPACE_BEGIN(vexa)


/* TODO */
// SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
// SDL_PixelFormat format;     /**< The format of the surface, read-only */
// int w;                      /**< The width of the surface, read-only. */
// int h;                      /**< The height of the surface, read-only. */
// int pitch;                  /**< The distance in bytes between rows of pixels, read-only */
// void *pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */
// int refcount;               /**< Application reference count, used when freeing surface */


class VX_NODISCARD Image
{
    friend class Window;
    friend class Font;

    struct M {
        bool is_loaded = false;
        void* image = nullptr;
        const char* path = nullptr;
    } m;

    static constexpr const char* MSG_LOAD_FAIL_PATH = {
        "Image::Load(): Failed to load image from path: '{}'"
    };


public:
    Image() noexcept = default;
    Image(Image&& other) noexcept;
    Image& operator= (Image&& other) noexcept;
    // delete copy
    Image(const Image&) = delete;
    Image& operator= (const Image&) = delete;
    //
    ~Image();


    // Load and return a image from path
    static Image Load(const char* path) noexcept;

    // Unload referenced image from memory
    static void Unload(RefMut<Image> image_ref) noexcept;

    bool operator== (const Image& other) const noexcept;

    void* ptr();
    Vec2i size();
    const char* path();
};


NAMESPACE_END(vexa)
