#include "vexa/core/log.hpp"
#include "vexa/Image.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Surface*>($OBJ))

using This = Image;



This::~Image() {
    Unload(RefMut{*this});
}

This::Image(Image&& other) noexcept
    : m(other.m)
{
    other.m = {};
}

Image& This::operator= (Image&& other) noexcept {
    if (this != address(other)) {
        if (m.is_loaded) SDL_DestroySurface(EXTERN_CAST(m.image));
        m = other.m;
        other.m = {};
    }
    return *this;
}


Image This::Load(const char* path) noexcept {
    Image build = {};

    build.m.image = SDL_LoadSurface(path);
    if (build.m.image == nullptr) {
        log::error(This::MSG_LOAD_FAIL_PATH, path);
    } else {
        build.m.is_loaded = true;
        build.m.path = path;
    }

    return build;
}


void This::Unload(RefMut<Image> image_ref) noexcept {
    if (image_ref.get().m.is_loaded) {
        SDL_DestroySurface(EXTERN_CAST(image_ref.get().m.image));
    }

    image_ref.get().m = {};
}


bool This::operator== (const Image& other) const noexcept {
    return (
        m.image == other.m.image &&
        m.path == other.m.path
    );
}

void* This::ptr() {
    return m.image;
}

Vec2i This::size() {
    return {
        EXTERN_CAST(m.image)->w,
        EXTERN_CAST(m.image)->h
    };
}


const char* This::path() {
    return m.path;
}


#undef EXTERN_CAST

NAMESPACE_END(vexa)
