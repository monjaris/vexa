#pragma once
#include "Image.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Texture
{
    friend class Renderer;


    static constexpr const char* MSG_LOAD_FAIL = {
        "Failed to load texture from path: '{}'"
    };


    static inline uint32 M_id_counter = 0;

    struct {
        uint32 id = 0;
        bool is_loaded = false;
        void* texture = nullptr;
        const char* path = nullptr;
    } m;

    static Texture M_Load(void* renderer_ptr, Image& image) noexcept;

public:
    Texture() noexcept = default;
    Texture(Texture&& other) noexcept;
    Texture& operator= (Texture&& other) noexcept;
    // delete copy
    Texture(const Texture&) = delete;
    Texture& operator= (const Texture&) = delete;
    //
    ~Texture();

    explicit operator bool() const noexcept;
    bool exists() const noexcept;
    uint32 id() const noexcept;
    const char* path() const noexcept;
    Vec2 pos() const noexcept;
};


NAMESPACE_END(vexa)
