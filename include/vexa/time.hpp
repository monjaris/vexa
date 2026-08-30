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

// Concepts
template<typename T>
struct is_duration : std::false_type {};

template<typename ValueT, uint64_t Scale>
struct is_duration<Duration<ValueT, Scale>> : std::true_type {};

template<typename T>
inline constexpr bool is_duration_v = is_duration<std::decay_t<T>>::value;

template<typename T>
concept DurationConcept = is_duration_v<T>;



// Date (time point)
template<DurationConcept> class TimePoint;
using Date = TimePoint<Nanos>;
using LongDate = TimePoint<Millis>;


// function declarations
void sleep(Nanos amount);
template<DurationConcept DurationT> void sleep(DurationT amount);
Date now();




// @arg ValueT - the underlying type to store duration as nanoseconds
// @arg t_ratio - nano:1, micro:1000, etc.
template<typename ValueType, uint64 t_ratio>
requires std::is_arithmetic_v<ValueType>
class VX_NODISCARD Duration
{
    ValueType m_nanos = 0;

    Duration(void* null, ValueType nanos): m_nanos(nanos) {}

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
    constexpr Duration operator+ (const Duration& other) const noexcept {
        return Duration{nullptr, m_nanos + other.m_nanos};
    }
    constexpr Duration operator- (const Duration& other) const noexcept {
        return Duration{nullptr, m_nanos - other.m_nanos};
    }


    consteval inline uint64 ratio() const noexcept { return t_ratio; }
    constexpr inline ValueT amount() const noexcept { return m_nanos / static_cast<ValueT>(t_ratio); }
    constexpr inline ValueT nanos() const noexcept { return m_nanos; }
    constexpr inline ValueT micros() const noexcept { return m_nanos / 1'000.0l; }
    constexpr inline ValueT millis() const noexcept { return m_nanos / 1'000'000.0l; }
    constexpr inline ValueT seconds() const noexcept { return m_nanos / 1'000'000'000.0l; }
};




template<DurationConcept DurationType>
class TimePoint {
public:
    using DurationT = DurationType;

private:
    DurationT m_since_epoch;


public:
    // default ctor
    constexpr TimePoint(): m_since_epoch(0) {};

    // main ctor
    template<DurationConcept DurationT>
    constexpr TimePoint(DurationT dur_since_epoch): m_since_epoch(dur_since_epoch) {}

    // { +=, -=, +, - } operators
    // <Date> += <DurationT>
    constexpr TimePoint& operator+= (DurationT duration) noexcept {
        m_since_epoch += duration;
        return *this;
    }
    // <Date> -= <DurationT>
    constexpr TimePoint& operator-= (DurationT duration) noexcept {
        m_since_epoch -= duration;
        return *this;
    }
    // <Date> + <DurationT>
    constexpr TimePoint operator+ (DurationT duration) noexcept {
        return {.m_since_epoch = m_since_epoch + duration};
    }
    // <Date> - <DurationT>
    constexpr TimePoint operator- (DurationT duration) noexcept {
        return {.m_since_epoch = m_since_epoch - duration};
    }
    // <Date> - <Date>
    constexpr DurationT operator- (const TimePoint& other) noexcept {
        return DurationT{m_since_epoch - other.m_since_epoch};
    }


    const DurationT& sinceEpoch() {
        return m_since_epoch;
    }

    DurationT elapsed() {
        return DurationT{now().m_since_epoch.nanos() - m_since_epoch.nanos()};
    }
};





template<DurationConcept DurationT>
void sleep(DurationT amount) {
    sleep(Nanos{static_cast<int64>(amount.nanos())});
}



NAMESPACE_END(vexa::time)
