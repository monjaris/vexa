#pragma once
#include "defs.hpp"
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


// a value with default value stored
template<typename T>
class CfgVal {
    T m_default;
    T m_value;
    bool m_set = false;
public:

    constexpr CfgVal (T default_and_initial_value)
        : m_default(default_and_initial_value), m_value(m_default), m_set(false)
    {}

    constexpr CfgVal& operator=(const T& new_value) {
        m_value = new_value;
        m_set = true;
        return *this;
    }

    auto value() const { return m_value; }

    // true if this value was explicitly assigned
    constexpr bool isSet() const { return m_set; }

    // restore the default value and mark this value as not explicitly set
    constexpr CfgVal& reset() {
        m_value = m_default;
        m_set = false;
        return *this;
    }

    // get default value of the config object
    T defaultVal() const { return m_default; }

    // bool operator== (T other) {
        // return value == other;
    // }

    // to access @member value implicitly
    constexpr operator T() const { return m_value; }

    // to access underlying members of value via `->`
    constexpr T* operator ->() { return &m_value; }
};



template<class T>
bool isContained(T cont, typename T::value_type elem) {
    for (usize i=0;  i < cont;  ++i) {
        if (cont[i] == elem) return true;
    }
    return false;
}


template<class T>
bool contains(T cont, typename T::ValueT elem) {
    for (usize i=0;  i < cont;  ++i) {
        if (cont[i] == elem) return true;
    }
    return false;
}



NAMESPACE_END(vexa)
