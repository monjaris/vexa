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
class OwnHeap
{
    T* m_ptr;

    // hiding because Alloc should be the way to do it
    // no need to use this class if you are not hallocating
public:
    OwnHeap(T* ptr) noexcept: m_ptr(ptr) {}
    ~OwnHeap() { delete m_ptr; }

    // delete copy
    OwnHeap(const OwnHeap&) = delete;
    OwnHeap& operator= (const OwnHeap&) = delete;

    // move ownership
    OwnHeap(OwnHeap&& other) noexcept: m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    // delete and move ownership
    OwnHeap& operator= (OwnHeap&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    static OwnHeap Alloc() noexcept {
        return OwnHeap(new T{});
    }

    template<class... Args>
    requires (sizeof...(Args) > 0)
    static OwnHeap Alloc(Args&&... args) noexcept {
        return OwnHeap(new T{forwardRV<Args>(args)...});
    }

    T* get() const noexcept {
        return m_ptr;
    }
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
