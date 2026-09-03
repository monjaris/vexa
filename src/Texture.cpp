#include "vexa/alt/SDL3.h"
#include "vexa/core/log.hpp"
#include "vexa/Texture.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Texture*>($OBJ))

using This = Texture;



Texture This::M_Load(void* renderer_ptr, Image& image) noexcept {
    SDL_Texture* texture_handle = SDL_CreateTextureFromSurface(
        CAST<SDL_Renderer*>(renderer_ptr), CAST<SDL_Surface*>(image.ptr())
    );
    Texture build;

    if (texture_handle == nullptr) {
        log::error(This::MSG_LOAD_FAIL, "");
    } else {
        build.m.is_loaded = true;
    }

    build.m.path = image.path();
    build.m.texture = texture_handle;

    return build;
}


This::operator bool() const noexcept {
    return m.is_loaded;
}

bool This::exists() const noexcept {
    return operator bool();
}

const char* This::path() const noexcept {
    return m.path;
}

Vec2 This::pos() const noexcept {
    return {
        CAST<fp32>(EXTERN_CAST(m.texture)->format),
        CAST<fp32>(EXTERN_CAST(m.texture)->h)
    };
}


This::~Texture() {
    // passing nullptr is no-op here
    SDL_DestroyTexture(EXTERN_CAST(m.texture));
    m.is_loaded = false;
}

#undef EXTERN_CAST

NAMESPACE_END(vexa)
