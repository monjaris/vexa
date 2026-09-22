#include <random>
#include "vexa/rng.hpp"

NAMESPACE_BEGIN(vexa)
NAMESPACE_BEGIN(rng)

template<IntConcept T>
T random(NoDeduce<T> min, NoDeduce<T> max) {
    thread_local static auto rng = std::mt19937_64{std::random_device{}()};
    std::uniform_int_distribution<T> dist{min, max};
    return dist(rng);
}

template<UintConcept T>
T random(NoDeduce<T> min, NoDeduce<T> max) {
    thread_local static auto rng = std::mt19937_64{std::random_device{}()};
    std::uniform_int_distribution<T> dist{min, max};
    return dist(rng);
}

template<FloatConcept T>
T random(NoDeduce<T> min, NoDeduce<T> max) {
    thread_local static auto rng = std::mt19937_64{std::random_device{}()};
    std::uniform_real_distribution<T> dist{min, max};
    return dist(rng);
}


// Instantiate templates here
#define INST_TEMPLATE_RANDOM($TYPE) \
    template $TYPE random<$TYPE>(NoDeduce<$TYPE>, NoDeduce<$TYPE>);

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
INST_TEMPLATE_RANDOM(fp32)
INST_TEMPLATE_RANDOM(fp64)


#undef INST_TEMPLATE_RANDOM

NAMESPACE_END(rng)
NAMESPACE_END(vexa)
