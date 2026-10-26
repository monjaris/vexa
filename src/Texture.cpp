#include "vexa/alt/SDL3.h"
#include "vexa/core/log.hpp"
#include "vexa/Texture.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Texture*>($OBJ))

using This = Texture;


This::Texture(Texture&& other)
{
    m = std::move(other.m);
    other.m = {};
}

Texture& This::operator= (Texture&& other) {
    if (this != address(other)) {
        SDL_DestroyTexture(EXTERN_CAST(m.texture));
        m = other.m;
        other.m = {};
    }
    return *this;
}

Texture This::M_Load(void* renderer_ptr, Image& image) {
    SDL_Texture* texture_handle = SDL_CreateTextureFromSurface(
        CAST<SDL_Renderer*>(renderer_ptr), CAST<SDL_Surface*>(image.ptr())
    );
    Texture build;

    if (texture_handle == nullptr) {
        log::error(This::MSG_LOAD_FAIL, image.path());
    } else {
        build.m.is_loaded = true;
        build.m.id = ++M_id_counter;
    }

    build.m.path = image.path();
    build.m.texture = texture_handle;

    return build;
}


This::operator bool() const {
    return m.is_loaded;
}

bool This::exists() const {
    return operator bool();
}

uint32 This::id() const {
    return m.id;
}

const char* This::path() const {
    return m.path;
}

Vec2 This::pos() const {
    return {
        CAST<fp32>(EXTERN_CAST(m.texture)->w),
        CAST<fp32>(EXTERN_CAST(m.texture)->h)
    };
}


This::~Texture() {
    SDL_DestroyTexture(EXTERN_CAST(m.texture));
    m = {};
}

#undef EXTERN_CAST

NAMESPACE_END(vexa)
