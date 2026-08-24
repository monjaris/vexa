#include "alt/SDL3.h"
#include <thread>
#include <chrono>
#include "time.hpp"
NAMESPACE_BEGIN(vexa::time)

namespace chrono = std::chrono;


void sleep(Nanos ns) {
    std::this_thread::sleep_for(chrono::nanoseconds{ns.amount()});
}

Date now() {
    Date date;
    auto now_ns = chrono::steady_clock::now().time_since_epoch().count();
    date = Date{Nanos{now_ns}};
    return date;
}


NAMESPACE_END(vexa::time)
