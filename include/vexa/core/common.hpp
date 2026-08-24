#pragma once
#include <concepts>
#include <print>
#include "vexa/alt/ini_list.hpp"
#include "defs.hpp"
// modules
#include "vexa/core/math.hpp"
#include "vexa/core/colors.hpp"
#include "vexa/core/shapes.hpp"
#include "vexa/core/vec.hpp"
#include "vexa/core/log.hpp"
#include "vexa/core/Flags.hpp"
NAMESPACE_BEGIN(vexa)


inline consteval usize cstr_len(const char* cstr) noexcept {
    usize n = 0;
    while (*cstr++ != '\0') ++n;
    return n;
}

template<typename T, usize N>
inline consteval usize item_size(const T (&array)[N]) noexcept {
    return sizeof(T);  (void)array;
}
// overload for containers with the underlying type that has ::value_type or ::ValueType
template<typename T> requires (
    requires { typename T::ValueType; } ||
    requires { typename T::value_type; }
) inline
consteval usize item_size(const T&) noexcept {
    if constexpr (requires { typename T::ValueType; }) return sizeof(typename T::ValueType);
    else return sizeof(typename T::value_type);
}



// a value with default value storage
template<typename T>
class CfgVal {
    T m_default;
    T value;
public:

    constexpr CfgVal (T default_and_initial_value)
        : m_default(default_and_initial_value), value(m_default)
    {}

    constexpr CfgVal& operator=(const T& new_value) {
        value = new_value;
        return *this;
    }

    // get default value of the config object
    const T& defaultVal() const { return m_default; }

    // to access @member value implicitly
    constexpr operator T() const noexcept { return value; }

    // to access underlying members of value via `->`
    constexpr T* operator ->() noexcept { return &value; }
};


template<class T>
class OwnPtr {
    T* m_ptr;
public:
    OwnPtr(T* ptr): m_ptr(ptr) {}
    ~OwnPtr() {}

    // delete copy ctor/operator
    explicit OwnPtr(const T& copy_ctor) = delete;
    OwnPtr& operator= (const T& copy_operator) = delete;

    // define move ctor/operator
    explicit OwnPtr(T&& other) {
        m_ptr = other.mptr;
    }
    OwnPtr& operator= (T&& other) {
        m_ptr = other.m_ptr;
        return *this;
    }

    T* get() { return m_ptr; }

    static T* Alloc() {
        return OwnPtr<T>(new T{});
    }
};



template<class T>
class Ref {
    const T* const m_data = nullptr;

public:
    Ref(T& data): m_data(&data) {}

    VX_NODISCARD const T& get() const noexcept { return *m_data; }
};


template<class T>
class RefMut {
    T* const m_data = nullptr;

public:
    RefMut(T& object): m_data(&object) {}

    const T& get() const {
        return *m_data;
    }
};


NAMESPACE_END(vexa)
