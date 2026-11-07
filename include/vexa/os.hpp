#pragma once
#include "vexa/core/defs.hpp"
#include "vexa/core/StrBuf.hpp"
#include <climits>
NAMESPACE_BEGIN(vexa::os)

constexpr uint32 FS_PATH_MAX = {
#   if defined VX_WINDOWS
        MAX_PATH
#   elif defined VX_GENERIC_UNIX || defined VX_MACOS
        PATH_MAX
#   elif VX_UNKNOWN_OS
        4096
#   endif
};


// exit the current process, just like std::exit()
[[noreturn]] void exitProcess(int exit_code);

StrBuf<FS_PATH_MAX> env(const char* env_var);
void setEnv(const char* env);  // IMPL!
void unsetEnv(const char* env);  // IMPL!

// get the current working directory
StrBuf<FS_PATH_MAX> cwd();
// set current working directory
bool setCwd(const char* dir);

StrBuf<FS_PATH_MAX> homeDir();

StrBuf<FS_PATH_MAX> execPath();

NAMESPACE_END(vexa::os)
