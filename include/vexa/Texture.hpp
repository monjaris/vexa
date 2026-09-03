#pragma once
#include "Image.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Texture
{
    friend class Renderer;


    static constexpr const char* MSG_LOAD_FAIL = {
        "Failed to load texture from path: '{}'"
    };

    struct M {
        bool is_loaded = false;
        void* texture = nullptr;
        const char* path = nullptr;
    } m;

    static Texture M_Load(void* renderer_ptr, Image& image) noexcept;

public:
    Texture() = default;
    Texture(Texture&&) = default;
    Texture& operator= (Texture&&) = default;
    // delete copy
    Texture(const Texture&) = delete;
    Texture& operator= (const Texture&) = delete;
    //
    ~Texture();

    explicit operator bool() const noexcept;
    bool exists() const noexcept;
    const char* path() const noexcept;
    Vec2 pos() const noexcept;
};


NAMESPACE_END(vexa)
