#pragma once
#include <concepts>
#include "core/defs.hpp"
NAMESPACE_BEGIN(vexa::time)


// Duration and variants
template<typename ValueT, uint64> requires std::is_arithmetic_v<ValueT>
class VX_NODISCARD Duration;
using Nanos = Duration<int64, 1lu>;
using Micros = Duration<int64, 1'000lu>;
using Millis = Duration<fp64, 1'000'000lu>;
using Seconds = Duration<fp64, 1'000'000'000lu>;

// Date (time point)
class Date;

// Concepts
template<typename T>
struct is_duration : std::false_type {};
template<typename ValueT, uint64 ratio>
struct is_duration<Duration<ValueT, ratio>> : std::true_type {};
template<typename T>
concept DurationConcept = is_duration<std::remove_cvref_t<T>>::value;

// function declarations
void sleep(Nanos amount);
template<DurationConcept DurationT> void sleep(DurationT amount);
Date now();




// @arg ValueT - the underlying type to store duration as nanoseconds
// @arg t_ratio - 1:nano, 1000:micro, etc.
template<typename ValueType, uint64 t_ratio>
requires std::is_arithmetic_v<ValueType>
class VX_NODISCARD Duration
{
    ValueType m_nanos = 0;

public:
    using ValueT = ValueType;
    static constexpr auto RATIO = t_ratio;

    // default ctor
    Duration() = delete;

    // explicit ctor
    explicit constexpr Duration(ValueT amount): m_nanos(amount * t_ratio) {}

    // { +=, -=, +, - } operators for <Duration>s
    constexpr Duration& operator+= (const Duration& duration) noexcept {
        m_nanos += duration.m_nanos;  return *this;
    }
    constexpr Duration& operator-= (const Duration& duration) noexcept {
        m_nanos -= duration.m_nanos;  return *this;
    }
    friend constexpr Duration operator+ (Duration left, const Duration& right) noexcept {
        left += right;  return left;
    }
    friend constexpr Duration operator- (Duration left, const Duration& right) noexcept {
        left -= right;  return left;
    }


    consteval inline uint64 ratio() const noexcept { return t_ratio; }
    constexpr inline ValueT amount() const noexcept { return m_nanos / static_cast<ValueT>(t_ratio); }
    constexpr inline ValueT nanos() const noexcept { return m_nanos; }
    constexpr inline ValueT micros() const noexcept { return m_nanos / 1'000.0l; }
    constexpr inline ValueT millis() const noexcept { return m_nanos / 1'000'000.0l; }
    constexpr inline ValueT seconds() const noexcept { return m_nanos / 1'000'000'000.0l; }
};





class Date {
    Nanos m_since_epoch;

public:
    // default ctor
    constexpr Date(): m_since_epoch(0) {};

    // main ctor
    template<DurationConcept DurationT>
    explicit constexpr Date(DurationT dur_since_epoch): m_since_epoch(dur_since_epoch) {}

    // assignment operator (<Date>=<Duration>)
    // template<DurationConcept DurationT>
    // constexpr Date& operator= (const DurationT& dur_since_epoch) {
        // m_since_epoch = dur_since_epoch;
        // return *this;
    // }

    // { +=, -=, +, - } operators
    // <Date> += <Nanos>
    constexpr Date& operator+= (Nanos duration) noexcept {
        m_since_epoch += duration;
        return *this;
    }
    // <Date> -= <Nanos>
    constexpr Date& operator-= (Nanos duration) noexcept {
        m_since_epoch -= duration;
        return *this;
    }
    // <Date> + <Nanos>
    friend constexpr Date operator+ (Date date, Nanos duration) noexcept {
        return date += duration;
    }
    // <Date> - <Nanos>
    friend constexpr Date operator- (Date date, Nanos duration) noexcept {
        return date -= duration;
    }
    // <Date> - <Date>
    friend constexpr Nanos operator- (const Date& left, const Date& right) noexcept {
        return left.m_since_epoch - right.m_since_epoch;
    }


    const Nanos& sinceEpoch() {
        return m_since_epoch;
    }

    Nanos elapsed() {
        return Nanos{now().m_since_epoch.nanos() - m_since_epoch.nanos()};
    }
};





template<DurationConcept DurationT>
void sleep(DurationT amount) {
    sleep(Nanos{static_cast<int64>(amount.nanos())});
}



NAMESPACE_END(vexa::time)
