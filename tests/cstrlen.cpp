#include "vexa.hpp"

namespace cn = vexa;

int main() {
    constexpr const char* cstr = "123456789012";

    using Dur = cn::time::Nanos;
    const char* dur_type = "";
    if constexpr (is_same_t<Dur, cn::time::Nanos>) dur_type = "ns";
    if constexpr (same_t<Dur, cn::time::Micros>) dur_type = "micros";
    if constexpr (same_t<Dur, cn::time::Millis>) dur_type = "ms";
    if constexpr (same_t<Dur, cn::time::Seconds>) dur_type = "secs";

    cn::log::print(cstr);
    auto start = cn::time::now<Dur>();
    auto sz = cn::cStrLen(cstr);
    auto finish = cn::time::now<Dur>();
    cn::log::print(cstr);

    auto elapsed = finish.m_date.m_value - start.m_date.m_value;
    cn::log::print("\n\nelapsed-time: {}{}", elapsed, dur_type);
    cn::log::print("lenght of c-string '{}' is: {}\n\n\n", cstr, sz);
}
