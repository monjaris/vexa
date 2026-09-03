#pragma once
#include "vexa/core/defs.hpp"
#include "vexa/core/utils.hpp"
NAMESPACE_BEGIN(vexa)

template<usize size, typename CharType = char8>
requires CharConcept<CharType> && (size > 0)
class VX_NODISCARD StrBuf
{
    using CharT = CharType;

    CharT m_buf[size] = {};
    usize m_len = 0;

public:
    constexpr StrBuf() noexcept = default;
    constexpr ~StrBuf() noexcept = default;

    constexpr StrBuf(const CharT* cstr) noexcept {
        m_len = cstrLen(cstr);

        if (m_len >= size) m_len = size - 1;

        ::memcpy(m_buf, cstr, m_len);
        m_buf[m_len] = '\0';
    }

    constexpr CharT* data() noexcept {
        return m_buf;
    }

    constexpr const CharT* cstr() const noexcept {
        return m_buf;
    }

    constexpr usize length() const noexcept {
        return m_len;
    }

    constexpr usize lengthMax() const noexcept {
        return size - 1;
    }
};

NAMESPACE_END(vexa)
