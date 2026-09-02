#include <unistd.h>
#include "vexa/os.hpp"
NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(os)

NAMESPACE_BEGIN(platform_detail)
NAMESPACE_END(platform_detail)

namespace detail = platform_detail;


auto cwd() noexcept -> StrBuf<PATH_MAX> {
    StrBuf<PATH_MAX> buf;
    ::getcwd(buf.data(), buf.lengthMax());
    return buf;
}

NAMESPACE_END(os)
NAMESPACE_END(vexa)
