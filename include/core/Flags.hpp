#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(cone)


class CN_NODISCARD Flags {
    using This = Flags;
    uint32 m_value;

public:
    using Value = uint32;

    // Ctor
    constexpr Flags (Value ini_value = 0) noexcept: m_value(ini_value) {}
    Flags (const Flags&) = default;


    // Getters
    CN_NODISCARD constexpr Value value() const noexcept { return m_value; }
    constexpr bool has(const Flags& flags) const noexcept { return (m_value & flags.m_value)!=0; }

    // sets the value directly
    void operator= (const This& other) noexcept {
        m_value = other.m_value;
    }
    // clears the flags
    constexpr This& reset() noexcept {
        m_value ^= m_value;  // m_value = 0
        return *this;
    }


    // add flag to base
    constexpr This& add(Value flag) noexcept {
        m_value |= flag;
        return *this;
    }
    constexpr This& add(This flag) noexcept {
        m_value |= flag.m_value;
        return *this;
    }

    // subtract flag from base
    constexpr This& sub(Value flag) noexcept {
        m_value &= ~flag;
        return *this;
    }
    constexpr This& sub(This flag) noexcept {
        m_value &= ~flag.m_value;
        return *this;
    }
};


NAMESPACE_END(cone)
