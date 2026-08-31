#include <string_view>
#include "vexa/Image.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<SDL_Surface*>($OBJ))

using This = Image;



This::~Image() {
    Unload(RefMut{*this});
}


Image This::Load(std::string_view path) {
    Image image;

    image.m.is_loaded = true;
    image.m.image = SDL_LoadSurface(path.data());
    image.m.path = path;
    image.m.size = {
        EXTERN_CAST(image.m.image)->w,
        EXTERN_CAST(image.m.image)->h
    };

    return image;
}


bool This::Unload(RefMut<Image> image_ref) {
    if (image_ref.get().m.is_loaded) {
        SDL_DestroySurface(EXTERN_CAST(image_ref.get().m.image));
    }
    bool was_loaded = image_ref.get().m.is_loaded;
    image_ref.get().m.is_loaded = false;
    return was_loaded;
}


Vec2i This::size() {
    return m.size;
}


std::string_view This::path() {
    return m.path;
}


#undef EXTERN_CAST

NAMESPACE_END(vexa)
