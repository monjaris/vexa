#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(mem)


template<typename T>
constexpr T* address(T& obj) {
    return __builtin_addressof(obj);
}
// overlad for non-const
template<typename T>
constexpr T* address(const T& obj) {
    return __builtin_addressof(obj);
}



template<typename T>
constexpr RmRef<T>&& move(T&& value) {
    return CAST<RmRef<T>&&>(value);
}


template<typename T>
constexpr T&& forward(RmRef<T>& value) {
    return CAST<T&&>(value);
}
// must overload
template<typename T>
constexpr T&& forward(RmRef<T>&& value)
{
    static_assert(!is_lvref<T>);
    return CAST<T&&>(value);
}




template<class T>
class Uptr
{
    T* m_ptr;

public:
    Uptr() = default;
    explicit Uptr(T* ptr): m_ptr(ptr) {}

    ~Uptr() { delete m_ptr; }

    // delete copy
    Uptr(const Uptr&) = delete;
    Uptr& operator= (const Uptr&) = delete;

    // move ownership
    Uptr(Uptr&& other): m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    // delete and move ownership
    Uptr& operator= (Uptr&& other) {
        if (this != &other) {
            this->reset(other.m_ptr);
            other.m_ptr = nullptr;
        }
        return *this;
    }

    static Uptr Alloc() {
        return Uptr(new T{});
    }

    template<class... Args>
    requires (sizeof...(Args) > 0)
    static Uptr Alloc(Args&&... args) {
        return Uptr(new T{forward<Args>(args)...});
    }

    void operator= (nullptrT null) {
        m_ptr = null;
    }

    void reset(T* new_ptr = nullptr) {
        T* old_ptr = m_ptr;
        m_ptr = new_ptr;
        delete old_ptr;
    }

    bool isNull() {
        return !m_ptr;
    }

    const T* get() const { return m_ptr; }
    T* get() { return m_ptr; }

    const T* operator-> () const { return m_ptr; }
    T* operator-> () { return m_ptr; }

    const T& operator* () const { return *m_ptr; }
    T& operator* () { return *m_ptr; }
};


template<class T>
class VX_NODISCARD Ref
{
    const T* const m_data = nullptr;

public:
    explicit Ref(T& data): m_data(&data) {}

    VX_NODISCARD const T& get() const { return *m_data; }
};


template<class T>
class VX_NODISCARD RefMut
{
    T* const m_data = nullptr;

public:
    explicit RefMut(T& object): m_data(&object) {}

    T& get() {
        return *m_data;
    }

    const T& getConst() const {
        return *m_data;
    }
};



NAMESPACE_END(mem)
NAMESPACE_END(vexa)
