#include "vexa/os.hpp"
#include <cstdlib>

#if defined VX_WINDOWS
    #include <direct.h>
    #define CHANGE_CWD ::_chdir
    #define GET_CWD ::_getcwd

#elif defined VX_GENERIC_UNIX || defined VX_MACOS
    #include <unistd.h>
    #define CHANGE_CWD ::chdir
    #define GET_CWD ::getcwd

#else
    #error "Unknown OS."
#endif


NAMESPACE_BEGIN(vexa::os)


[[noreturn]] void exitProcess(int exit_code) {
    ::exit(exit_code);
}

auto cwd() -> StrBuf<FS_PATH_MAX> {
    decltype(cwd()) buf;

    if (GET_CWD(buf.data(), buf.lengthMax())) {
        return buf;
    }
    else {
        return {};
    }
}

bool setCwd(StrBuf<FS_PATH_MAX> dir) {
    return CHANGE_CWD(dir.cstr()) == 0;
}


NAMESPACE_END(vexa::os)
