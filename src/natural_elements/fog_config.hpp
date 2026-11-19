#pragma once
#include <cstdint> // for std::uint32_t

namespace liminal {

struct FogConfig {
    std::uint32_t seed = 42; // Seed for the random properties of the fog bank (its color index)
    float x = 0.0f; // Initial horizontal position of the fog area (left edge, pixels)
    float y = 150.0f; // Vertical position of the fog area (top edge, pixels from the top)
    float width = 400.0f; // Width of the fog area
    float height = 450.0f; // Height of the fog area
    float speed = 2.0f; // Speed at which the fog moves horizontally
    float density = 0.5f; // Density of the fog, affecting its opacity
};

} // namespace liminal
