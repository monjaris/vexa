#include "vexa/Texture.hpp"
#include "vexa/alt/SDL3.h"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Texture*>($OBJ))

using This = Texture;


Vec2 This::pos() const {
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
