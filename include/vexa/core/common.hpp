#pragma once
#include "vexa/alt/ini_list.hpp"
#include "defs.hpp"
// modules
#include "vexa/core/utils.hpp"
#include "vexa/core/math.hpp"
#include "vexa/core/memory.hpp"
#include "vexa/core/colors.hpp"
#include "vexa/core/shapes.hpp"
#include "vexa/core/vec.hpp"
#include "vexa/core/log.hpp"
#include "vexa/core/Flags.hpp"
#include "vexa/core/Key.hpp"
#include "vexa/core/MouseBtn.hpp"
#include "vexa/core/Angle.hpp"
NAMESPACE_BEGIN(vexa)


template<class StdContainerType>
constexpr usize stdcont_len = std::tuple_size_v<StdContainerType>;


// a value with default value storage
template<typename T>
class CfgVal {
    T m_default;
    T m_value;
public:

    constexpr CfgVal (T default_and_initial_value)
        : m_default(default_and_initial_value), m_value(m_default)
    {}

    constexpr CfgVal& operator=(const T& new_value) {
        m_value = new_value;
        return *this;
    }

    auto value() const noexcept { return m_value; }

    // get default value of the config object
    T defaultVal() const noexcept { return m_default; }

    // bool operator== (T other) {
        // return value == other;
    // }

    // to access @member value implicitly
    constexpr operator T() const noexcept { return m_value; }

    // to access underlying members of value via `->`
    constexpr T* operator ->() noexcept { return &m_value; }
};



NAMESPACE_END(vexa)
