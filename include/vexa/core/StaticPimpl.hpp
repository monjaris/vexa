#pragma once
#include "defs.hpp"
#include <cstddef>
NAMESPACE_BEGIN(vexa)


template<
    // An incomplete type we statically implement
    class ImplT,
    // the size of the memory we statically allocate for ImplT object
    usize storage_size,
    // enables compilation error on `(storage_size != sizeof(ImplT))` (instead of `<`)
    bool pedantic = false,
    // alignment of storage, rarely needs to be explicitly specified
    usize alignment = alignof(std::max_align_t)
>
class StaticPimpl
{
    static constexpr usize m_size = storage_size;

    alignas(alignment) std::byte m_data[m_size];

    ImplT* mGet() { return LAUNDER(reinterpret_cast<ImplT*>(m_data)); }
    const ImplT* mGetConst() const { return LAUNDER(reinterpret_cast<const ImplT*>(m_data)); }

public:
    StaticPimpl() noexcept = default;

    consteval bool ensure() {
        if constexpr (pedantic) {
            static_assert(storage_size == sizeof(ImplT),
                "Implementation type's size and specified size on declaration are not equal\n"
            );
        } else {
            static_assert(storage_size >= sizeof(ImplT),
                "Implementation type's size is less than specified size on declaration\n"
            );
        }
    }

    constexpr void construct() {
        if constexpr (pedantic) {
            static_assert(storage_size == sizeof(ImplT),
                "Implementation type's size and specified size on declaration are not equal\n"
            );
        } else {
            static_assert(storage_size >= sizeof(ImplT),
                "Implementation type's size is less than specified size on declaration\n"
            );
        }

        new (m_data) ImplT {};
    }

    constexpr void destruct() {
        mGet()->~ImplT();
    }

    const ImplT* data() const { return mGetConst(); }
    ImplT* data() { return mGet(); }

    const ImplT* operator-> () const { return mGetConst(); }
    ImplT* operator-> () { return mGet(); }

    constexpr auto size() { return m_size; }
};


NAMESPACE_END(vexa)
