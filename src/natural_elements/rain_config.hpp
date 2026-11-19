#pragma once
#include <cstdint> // for std::uint8_t, std::uint32_t
#include "color_palettes/color_structs.hpp" // for kColorRampSize

namespace liminal {

struct RainConfig {
    std::uint32_t seed = 42; // Seed for drop placement, sizes and colors
    int count = 300; // Number of raindrops in the system
    float minLength = 8.0f; // Minimum length of a raindrop
    float maxLength = 24.0f; // Maximum length of a raindrop
    float minSpeed = 200.0f; // Minimum speed of a raindrop
    float maxSpeed = 700.0f; // Maximum speed of a raindrop
    std::uint8_t minColorIndex = 0; // Minimum color index for raindrops
    std::uint8_t maxColorIndex = kColorRampSize - 1; // Maximum color index for raindrops
    float maxIntensity = 3.0f; // Maximum intensity of the rain system
    float intensity = 1.0f; // Current intensity of the rain system, affecting speed and density
};

} // namespace liminal
