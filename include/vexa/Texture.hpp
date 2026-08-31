#pragma once
#include "Image.hpp"
NAMESPACE_BEGIN(vexa)


class VX_NODISCARD Texture
{
    friend class Renderer;

    struct M {
        bool is_loaded = false;
        void* texture = nullptr;
    } m;

public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture& operator= (const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator= (Texture&&) = default;
    //
    ~Texture();

    Vec2 pos() const;
};


NAMESPACE_END(vexa)
