#pragma once

#include <cstdint>
#include <random>

namespace liminal {

// Deterministic random number generator for procedural generation.
// std::mt19937 (Mersenne Twister) is fully specified by the C++ standard:
// the same seed produces the same sequence on every compiler and platform.
// Unlike raylib's GetRandomValue, it is a local object rather than global state,
// so seeding the mountains does not affect e.g. the rain.
using Rng = std::mt19937;

/**
 * Uniformly distributed float in [min, max).
 *
 * Deliberately not std::uniform_real_distribution: the standard specifies the
 * engine but not the distributions, so libstdc++, libc++ and MSVC may turn the same
 * seed into different floats. This mapping is reproducible everywhere: take the
 * top 24 bits of the 32-bit output (a float has a 24-bit significand, so every
 * value is exactly representable) and scale them to [0, 1).
 *
 * @param rng The generator; passed by reference so that its state advances
 * @param min Lower bound (inclusive)
 * @param max Upper bound (exclusive)
 */
inline float randomFloat(Rng& rng, float min, float max) noexcept {
    const float unit = static_cast<float>(rng() >> 8) * (1.0f / 16777216.0f); // 2^24
    return min + (max - min) * unit;
}

} // namespace liminal
