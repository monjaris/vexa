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


NAMESPACE_END(rng)
NAMESPACE_END(vexa)
