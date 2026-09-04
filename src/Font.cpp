#include "vexa/alt/SDL3-TTF.hpp"
#include "vexa/Font.hpp"
#include "vexa/core/log.hpp"
NAMESPACE_BEGIN(vexa)

#define EXTERN_CAST($OBJ) (static_cast<TTF_Font*>($OBJ))

#define FN "Font::{}(): "

using This = Font;


This::Font() noexcept = default;

This::~Font() noexcept {
    if (m.is_loaded) {
        Unload(RefMut{*this});
    }
}


This::Font(Font&& other) noexcept
{
    m = std::move(other.m);
    other.m = {};
}

Font& This::operator= (Font&& other) noexcept {
    if (this != address(other)) {
        TTF_CloseFont(EXTERN_CAST(m.font_handle));
        m = std::move(other.m);
        other.m.font_handle = {};
    }
    return *this;
}


Font This::Load(const char* path, usize load_size) noexcept {
    if (!This::ttf_context_loaded) {
        log::error(FN"{}", __func__, This::MSG_CONTEXT_UNINITED);
    }

    Font build;

    build.m.font_handle = TTF_OpenFont(path, load_size);
    if (build.m.font_handle == nullptr) {
        log::error(FN"{}", __func__, This::MSG_LOAD_FAIL);
    } else {
        build.m.is_loaded = true;
        build.m.path = path;
        build.m.size = load_size;
    }

    return build;
}

void This::Unload(RefMut<Font> font) noexcept {
    // if (!This::ttf_context_loaded) {
        // log::error(FN"{}", __func__, This::MSG_CONTEXT_UNINITED);
    // }

    TTF_CloseFont(EXTERN_CAST(font.getConst().m.font_handle));
    font.get().m = {};
}


Image This::createImage(const char* text, Color bg, Color fg) noexcept {
    SDL_Surface* surface = TTF_RenderText_Shaded(
        EXTERN_CAST(m.font_handle), text, cstrLen(text),
        {fg.r, fg.g, fg.b, fg.a},
        {bg.r, bg.g, bg.b, bg.a}
    );

    Image build;
    if (surface == nullptr) {
        log::error(FN"{}", __func__, This::MSG_CREATE_IMAGE_FAIL);
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


void This::setSize(fp32 font_size) noexcept {
    m.size = font_size;
    TTF_SetFontSize(EXTERN_CAST(m.font_handle), font_size);
}


const char* This::path() const noexcept {
    return m.path;
}

fp32 This::size() const noexcept {
    return m.size;
}

NAMESPACE_END(vexa)
