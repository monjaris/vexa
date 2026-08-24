#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)



template<typename T>
class VX_NODISCARD Flags {
public:
    using ValueT = T;
    using UnderT = underlying_t<ValueT>;

private:
    using This = Flags;
    ValueT m_value = {};

public:
    //  Ctors  //
    constexpr Flags (ValueT ini_value = ValueT{}) noexcept: m_value(ini_value) {}
    Flags (const This&) = default;
    Flags (This&&) = default;


    //  Getters  //
    VX_NODISCARD constexpr ValueT value() const noexcept {
        return m_value;
    }
    VX_NODISCARD constexpr UnderT intValue() const noexcept {
        return CAST(underlying_t<ValueT>, m_value);
    }

    //  has/has-not  //
    constexpr bool has(const This& flags) const noexcept {
        return (m_value & flags.m_value) != ValueT{};
    }
    constexpr bool hasNot(const This& flags) const noexcept {
        return (m_value & flags.m_value) == ValueT{};
    }

    // copy operator
    void operator= (const This& other) noexcept {
        m_value = other.m_value;
    }

    // clears the flags
    constexpr This& reset() noexcept {
        m_value = ValueT{};
        return *this;
    }

    // add flag to value
    constexpr This& add(This flag) noexcept {
        m_value |= flag.m_value;
        return *this;
    }
    constexpr This& add(ValueT flag) noexcept {
        m_value |= flag;
        return *this;
    }

    // subtract flag from base
    constexpr This& sub(ValueT flag) noexcept {
        m_value &= ~flag;
        return *this;
    }
    constexpr This& sub(This flag) noexcept {
        m_value &= ~flag.m_value;
        return *this;
    }
};



NAMESPACE_END(vexa)
