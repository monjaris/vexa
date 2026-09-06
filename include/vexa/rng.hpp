#pragma once
#include <numeric>
#include "core/defs.hpp"

NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(rng)

// Fast Xorshift prng implementation
template<typename T>
requires IntConcept<T> || UintConcept<T>
class VX_NODISCARD FastRand {
public:
    using ValueT = uint64;

private:
    ValueT state;

    static constexpr uint64 magic_1 = 13;
    static constexpr uint64 magic_2 = 7;
    static constexpr uint64 magic_3 = 17;
    static constexpr uint64 magic_4 = 24;
    static constexpr uint64 magic_5 = 8;

public:
    explicit constexpr FastRand(ValueT seed) noexcept
        : state(seed)
    {}

    constexpr ValueT generate() noexcept {
        ValueT x = state;

        x ^= x << magic_1;
        x ^= x >> magic_2;
        x ^= x << magic_3;
        x ^= x >> magic_4;
        x ^= x << magic_5;

        state = x;
        return x;
    }
};

template<IntConcept T>
T random(NoDeduce<T> min, NoDeduce<T> max);

template<UintConcept T>
T random(NoDeduce<T> min, NoDeduce<T> max);


// Instantiate templates here
#define INST_TEMPLATE_RANDOM($TYPE) \
    extern template $TYPE random<$TYPE>(NoDeduce<$TYPE>, NoDeduce<$TYPE>);

INST_TEMPLATE_RANDOM(int8)
INST_TEMPLATE_RANDOM(int16)
INST_TEMPLATE_RANDOM(int32)
INST_TEMPLATE_RANDOM(int64)
//
INST_TEMPLATE_RANDOM(uint8)
INST_TEMPLATE_RANDOM(uint16)
INST_TEMPLATE_RANDOM(uint32)
INST_TEMPLATE_RANDOM(uint64)
//


#undef INST_TEMPLATE_RANDOM

NAMESPACE_END(rng)
NAMESPACE_END(vexa)
