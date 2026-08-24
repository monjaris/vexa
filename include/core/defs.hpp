#pragma once
#include "types.hpp"

#define NAMESPACE_BEGIN(_name) namespace _name {
#define NAMESPACE_END(_name) }
#define CAST(_type_name, _value) static_cast<_type_name>(_value)
#define TODO(_msg) auto _vexa_todo = _msg
#define IF_THEN(_cond, _stmt) if((_cond)) {DEFINE_STMT(_stmt)}
#define CASE_OR(_case1, _case2)  case _case1: case _case2

#define DEBUG_LN() (void)(vexa::log::debug("{}:{} -> {}()", __FILE__, __LINE__, __func__), "")
#define DEBUG_FUNC_MODE __func__
#define DEBUG_FUNC_TEMPLATE(_mode) DEFINE_STMT(vexa::log::debug("{}()", _mode);)
#define DEBUG_FUNC() DEBUG_FUNC_TEMPLATE(DEBUG_FUNC_MODE)


#define DO_PRAGMA(_x) _Pragma(#_x)
#define DEFINE_STMT(_stmt) do {_stmt} while(false);
#define IGNORE_WARNING_BEGIN(_diag) \
    DO_PRAGMA(GCC diagnostic push) \
    DO_PRAGMA(GCC diagnostic ignored _diag)
#define IGNORE_WARNING_END(_diag_optional_arg) \
    DO_PRAGMA(GCC diagnostic pop)



#define VX_NODISCARD  [[nodiscard]]

#define VX_STATIC_ERR(_msg) static_assert(false, _msg)

#define VX_STATIC_CLASS : private CN_SC
class CN_SC {CN_SC()=default; CN_SC(const CN_SC&)=delete; CN_SC& operator=(const CN_SC&)=delete;};

#define VX_UNUSE(...)  (unuse_symbol(__VA_ARGS__));
namespace vexa { template<typename... Args> constexpr void unuse_symbol(Args&&...) noexcept {} }
