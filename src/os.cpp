#include "vexa/os.hpp"


#if defined(_WIN32)
    #include <direct.h>
    #define CHANGE_DIR ::_chdir

#elif defined(__unix__) || defined(__APPLE__)
    #include <unistd.h>
    #define CHANGE_DIR ::chdir

#else
    #error "Unknown OS."
#endif


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

bool setCwd(StrBuf<PATH_MAX> dir) noexcept {
    return CHANGE_DIR(dir.cstr()) != 0;
}


NAMESPACE_END(os)
NAMESPACE_END(vexa)
