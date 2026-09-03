#include "vexa/core/log.hpp"
#include "vexa/Image.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Surface*>($OBJ))

using This = Image;



This::~Image() {
    Unload(RefMut{*this});
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


bool This::Unload(RefMut<Image> image_ref) noexcept {
    if (image_ref.get().m.is_loaded) {
        SDL_DestroySurface(EXTERN_CAST(image_ref.get().m.image));
    }
    bool was_loaded = image_ref.get().m.is_loaded;
    image_ref.get().m.is_loaded = false;
    return was_loaded;
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
