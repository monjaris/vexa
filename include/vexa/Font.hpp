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
        fp32 size = 0;
    } m;


    static constexpr const char* MSG_LOAD_FAIL = {
        "Failed to load font from path: "
    };

    static constexpr const char* MSG_CREATE_IMAGE_FAIL = {
        "Failed to create image from font: "
    };

    static constexpr const char* MSG_CONTEXT_UNINITED = {
        "FONT subsystem(Engine::FONT) is not initialized"
    };

    // `ttf_context_loaded` turns true when Engine initializes Engine::FONT subsystem
    friend class Engine;
    static inline bool ttf_context_loaded = false;


public:
    // ctor
    Font() noexcept;
    // rule of 5
    ~Font() noexcept;
    Font(Font&& other) noexcept;
    Font& operator= (Font&& other) noexcept;
    Font(const Font&) noexcept = delete;
    Font& operator= (const Font&) noexcept = delete;

    static Font Load(const char* path, usize load_size) noexcept;
    static void Unload(RefMut<Font> font) noexcept;

    Image createImage(const char* text, Color bg, Color fg) noexcept;
    bool exists() const noexcept;

    void setSize(fp32 font_size) noexcept;

    const char* path() const noexcept;
    fp32 size() const noexcept;
};


NAMESPACE_END(vexa)
