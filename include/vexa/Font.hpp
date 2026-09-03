#pragma once
#include "core/defs.hpp"
#include "core/memory.hpp"
#include "core/colors.hpp"
#include "vexa/Image.hpp"
#include "vexa/Texture.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Font
{
    struct {
        bool is_loaded = false;
        void* font_handle = nullptr;
        const char* path = nullptr;

        usize size;
    } m;

    static constexpr const char* MSG_LOAD_FAIL = {
        "Font::Load(): Failed to load font from path: '{}'"
    };

    static constexpr const char* MSG_CREATE_IMAGE_FAIL = {
        "Font::createImage(): Failed to create image from font: '{}'"
    };


public:
    Font() noexcept;
    ~Font() noexcept;

    static Font Load(const char* path, usize load_size) noexcept;
    static void Unload(RefMut<Font> font) noexcept;

    Image createImage(const char* text, Color bg, Color fg) noexcept;
    bool exists() const noexcept;

    void setSize(uint64 font_size) noexcept;

    const void* ptr() const noexcept;
    const char* path() const noexcept;
    usize size() const noexcept;
};


NAMESPACE_END(vexa)
