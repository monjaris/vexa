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
        uint32 id = 0;
        bool is_loaded = false;
        void* font_handle = nullptr;
        const char* path = nullptr;
        fp32 size = 0;
    } m;

    static inline uint32 M_id_counter = 0;


    // `ttf_context_loaded` turns true when Engine initializes Engine::FONT subsystem
    friend class Engine;
    static inline bool m_context_init = false;

    static bool M_InitSystem();
    static void M_QuitSystem();


    static constexpr const char* MSG_LOAD_FAIL = {
        "Failed to load font from path: "
    };

    static constexpr const char* MSG_CREATE_IMAGE_FAIL = {
        "Failed to create image from font: "
    };

    static constexpr const char* MSG_CONTEXT_UNINITED = {
        "FONT subsystem(Engine::FONT) is not initialized"
    };

public:
    // ctor
    Font();
    // rule of 5
    ~Font();
    Font(Font&& other);
    Font& operator= (Font&& other);
    Font(const Font&) = delete;
    Font& operator= (const Font&) = delete;

    static Font Load(const char* path, usize load_size);
    static void Unload(RefMut<Font> font);

    Image createImage(const char* text, Color bg, Color fg);
    bool exists() const;

    void setSize(fp32 font_size);

    const char* path() const;
    fp32 size() const;
};


NAMESPACE_END(vexa)
