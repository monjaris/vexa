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
        const char* path;
    } m;

    static Texture M_Load(void* renderer_ptr, Image image);

public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture& operator= (const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator= (Texture&&) = default;
    //
    ~Texture();

    explicit operator bool() const noexcept;
    bool error() const noexcept;
    const char* path() const noexcept;
    Vec2 pos() const noexcept;
};


NAMESPACE_END(vexa)
