#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(memory)


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
    explicit Ref(T& data): m_data(&data) {}

    VX_NODISCARD const T& get() const noexcept { return *m_data; }
};


template<class T>
class RefMut {
    T* const m_data = nullptr;

public:
    explicit RefMut(T& object): m_data(&object) {}

    T& get() noexcept {
        return *m_data;
    }

    const T& getConst() const noexcept {
        return *m_data;
    }
};



NAMESPACE_END(memory)
NAMESPACE_END(vexa)
