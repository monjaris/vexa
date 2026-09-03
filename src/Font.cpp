#include "vexa/alt/SDL3-TTF.hpp"
#include "vexa/Font.hpp"
#include "vexa/core/log.hpp"
NAMESPACE_BEGIN(vexa)

using This = Font;


This::Font() noexcept = default;

This::~Font() noexcept {
    if (!m.is_loaded) {
        Unload(RefMut{*this});
    }
}


Font This::Load(const char* path, usize load_size) noexcept {
    Font build;

    build.m.font_handle = TTF_OpenFont(path, load_size);
    if (build.m.font_handle == nullptr) {
        log::error(This::MSG_LOAD_FAIL, build.path());
    } else {
        build.m.is_loaded = true;
        build.m.path = path;
    }

    return build;
}

void This::Unload(RefMut<Font> font) noexcept {
    TTF_CloseFont(CAST<TTF_Font*>(font.getConst().m.font_handle));
    font.get().m.is_loaded = false;
    font.get().m.path = nullptr;
}


Image This::createImage(const char* text, Color bg, Color fg) noexcept {
    SDL_Surface* surface = TTF_RenderText_Shaded(
        CAST<TTF_Font*>(m.font_handle), text, m.size,
        {fg.r, fg.g, fg.b, fg.a},
        {bg.r, bg.g, bg.b, bg.a}
    );

    Image build;
    if (surface == nullptr) {
        log::error(This::MSG_CREATE_IMAGE_FAIL, m.path);
    } else {
        build.m.image = surface;
        build.m.is_loaded = true;
        build.m.path = m.path;
    }

    return build;
}


bool This::exists() const noexcept {
    return m.is_loaded;
}


void This::setSize(uint64 font_size) noexcept {
    m.size = font_size;
}


// const void* This::ptr() const noexcept {
    // return m.font_handle;
// }

const char* This::path() const noexcept {
    return m.path;
}

usize This::size() const noexcept {
    return m.size;
}

NAMESPACE_END(vexa)
