#include "vexa/vexa.hpp"

#define LOGGER  vexa::log::info
#define LOG(_msg)  LOGGER(_msg);
#define LOGV(_msg, ...)  LOGGER(_msg, __VA_ARGS__);

namespace mt = vexa::time;

int main()
{
    LOG("-- BEGIN")

    auto now = mt::now();
    LOGV("{}", now.sinceEpoch().nanos());

    LOG("-- END");
}
