#pragma once
#include "vexa/core/defs.hpp"
#include "vexa/core/StrBuf.hpp"
#include <climits>
NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(os)


StrBuf<PATH_MAX> cwd();
bool setCwd(StrBuf<PATH_MAX> dir);


NAMESPACE_END(os)
NAMESPACE_END(vexa)
