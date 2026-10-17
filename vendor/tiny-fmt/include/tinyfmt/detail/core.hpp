// Formatting library for C++ - the core API for char/UTF-8
//
// Copyright (c) 2012 - present, Victor Zverovich and {fmt} contributors
// All rights reserved.
//
// For the license information refer to format.h.
//
// Compatibility shim: the canonical core API now lives in ../tfmt.hpp
// (namespace tfmt, TFMT_* macros). This header keeps the original {fmt}
// macro names (FMT_*) working for the un-renamed headers in this
// directory (format-inl.hpp) so that there is only one copy
// of the core API in the codebase.
#ifndef FMT_CORE_H_
#define FMT_CORE_H_

// Map the original FMT_* macro names to their TFMT_* equivalents.
// These must be defined before including ../tfmt.hpp because its
// header-only opt-in (TFMT_HEADER_ONLY) pulls in format.hpp, which
// uses the FMT_* names while tfmt.hpp is still being processed.
#define FMT_ALWAYS_INLINE TFMT_ALWAYS_INLINE
#define FMT_API TFMT_API
#define FMT_APPLY_VARIADIC(expr) TFMT_APPLY_VARIADIC(expr)
#define FMT_ASSERT(condition, message) TFMT_ASSERT(condition, message)
#define FMT_BEGIN_EXPORT TFMT_BEGIN_EXPORT
#define FMT_BEGIN_NAMESPACE TFMT_BEGIN_NAMESPACE
#define FMT_BUILTIN TFMT_BUILTIN
#define FMT_BUILTIN_TYPES TFMT_BUILTIN_TYPES
#define FMT_CATCH(x) TFMT_CATCH(x)
#define FMT_CLANG_VERSION TFMT_CLANG_VERSION
#define FMT_CONSTEVAL TFMT_CONSTEVAL
#define FMT_CONSTEXPR TFMT_CONSTEXPR
#define FMT_CONSTEXPR20 TFMT_CONSTEXPR20
#define FMT_CPLUSPLUS TFMT_CPLUSPLUS
#define FMT_DEPRECATED TFMT_DEPRECATED
#define FMT_ENABLE_IF(...) TFMT_ENABLE_IF(__VA_ARGS__)
#define FMT_END_EXPORT TFMT_END_EXPORT
#define FMT_END_NAMESPACE TFMT_END_NAMESPACE
#define FMT_EXPORT TFMT_EXPORT
#define FMT_FALLTHROUGH TFMT_FALLTHROUGH
#define FMT_GCC_VERSION TFMT_GCC_VERSION
#define FMT_GLIBCXX_RELEASE TFMT_GLIBCXX_RELEASE
#define FMT_HAS_BUILTIN(x) TFMT_HAS_BUILTIN(x)
#define FMT_HAS_CPP14_ATTRIBUTE(attribute) \
  TFMT_HAS_CPP14_ATTRIBUTE(attribute)
#define FMT_HAS_CPP17_ATTRIBUTE(attribute) \
  TFMT_HAS_CPP17_ATTRIBUTE(attribute)
#define FMT_HAS_CPP_ATTRIBUTE(x) TFMT_HAS_CPP_ATTRIBUTE(x)
#define FMT_HAS_FEATURE(x) TFMT_HAS_FEATURE(x)
#define FMT_HAS_INCLUDE(x) TFMT_HAS_INCLUDE(x)
#define FMT_ICC_VERSION TFMT_ICC_VERSION
#define FMT_INLINE TFMT_INLINE
#define FMT_LIBCPP_VERSION TFMT_LIBCPP_VERSION
#define FMT_MSC_VERSION TFMT_MSC_VERSION
#define FMT_NODISCARD TFMT_NODISCARD
#define FMT_NORETURN TFMT_NORETURN
#define FMT_NO_UNIQUE_ADDRESS TFMT_NO_UNIQUE_ADDRESS
#define FMT_OPTIMIZE_SIZE TFMT_OPTIMIZE_SIZE
#define FMT_PRAGMA_CLANG(x) TFMT_PRAGMA_CLANG(x)
#define FMT_PRAGMA_GCC(x) TFMT_PRAGMA_GCC(x)
#define FMT_PRAGMA_IMPL(x) TFMT_PRAGMA_IMPL(x)
#define FMT_PRAGMA_MSVC(x) TFMT_PRAGMA_MSVC(x)
#define FMT_TRY TFMT_TRY
#define FMT_TYPE_CONSTANT(Type, constant) TFMT_TYPE_CONSTANT(Type, constant)
#define FMT_UNICODE TFMT_UNICODE
#define FMT_USE_CONSTEVAL TFMT_USE_CONSTEVAL
#define FMT_USE_CONSTEXPR TFMT_USE_CONSTEXPR
#define FMT_USE_EXCEPTIONS TFMT_USE_EXCEPTIONS
#define FMT_USE_INT128 TFMT_USE_INT128
#define FMT_USE_LOCALE TFMT_USE_LOCALE
#define FMT_USE_OPTIMIZE_PRAGMA TFMT_USE_OPTIMIZE_PRAGMA
#define FMT_VERSION TFMT_VERSION
#define FMT_VISIBILITY(value) TFMT_VISIBILITY(value)
#define FMT_WIN32 TFMT_WIN32

#endif  // FMT_CORE_H_
