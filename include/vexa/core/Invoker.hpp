#pragma once
#include "defs.hpp"
NAMESPACE_BEGIN(vexa)

// feature macro: INVOKE_OPERATOR_OVERLOAD


#define INVOKE_OPERATOR_OVERLOAD

// template forward declaration
template<class> class Invoker;


template<class RetT, class... Args>
class VX_NODISCARD Invoker<RetT(Args...)>
{
    RetT (*m_fn_ptr)(Args...);

public:
    Invoker() noexcept = default;

    template<class Invokable>
    Invoker(Invokable invokable) noexcept {
        m_fn_ptr = invokable;
    }

    Invoker(nullptrT invokable) = delete;

    constexpr RetT call(Args&&... args) {
        return m_fn_ptr(forwardRV<Args>(args)...);
    }

#if defined(INVOKE_OPERATOR_OVERLOAD)
    constexpr RetT operator() (Args&&... args) {
        return this->call(forwardRV(args)...);
    }
#endif
};


NAMESPACE_END(vexa)
