#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)
inline NAMESPACE_BEGIN(memory)


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
constexpr rm_ref_t<T>&& move(T&& value) {
    return CAST<rm_ref_t<T>&&>(value);
}


template<typename T>
constexpr T&& forwardRV(RemoveReferenceImpl<T>& value) noexcept {
    return CAST<T&&>(value);
}
// must overload
template<typename T>
constexpr T&& forwardRV(RemoveReferenceImpl<T>&& value) noexcept
requires (!IsLvalReference<T>::Value)
{
    return CAST<T&&>(value);
}




template<class T>
class Uptr
{
    T* m_ptr;

public:
    Uptr() noexcept = default;
    explicit Uptr(T* ptr) noexcept: m_ptr(ptr) {}

    ~Uptr() noexcept { delete m_ptr; }

    // delete copy
    Uptr(const Uptr&) = delete;
    Uptr& operator= (const Uptr&) = delete;

    // move ownership
    Uptr(Uptr&& other) noexcept: m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    // delete and move ownership
    Uptr& operator= (Uptr&& other) noexcept {
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
        return Uptr(new T{forwardRV<Args>(args)...});
    }

    void operator= (nullptrT null) noexcept {
        m_ptr = null;
    }

    void reset(T* new_ptr = nullptr) noexcept {
        T* old_ptr = m_ptr;
        m_ptr = new_ptr;
        delete old_ptr;
    }

    bool isNull() {
        return !m_ptr;
    }

    const T* get() const noexcept { return m_ptr; }
    T* get() noexcept { return m_ptr; }

    const T* operator-> () const noexcept { return m_ptr; }
    T* operator-> () noexcept { return m_ptr; }

    const T& operator* () const noexcept { return *m_ptr; }
    T& operator* () noexcept { return *m_ptr; }
};


template<class T>
class VX_NODISCARD Ref
{
    const T* const m_data = nullptr;

public:
    explicit Ref(T& data): m_data(&data) {}

    VX_NODISCARD const T& get() const noexcept { return *m_data; }
};


template<class T>
class VX_NODISCARD RefMut
{
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
