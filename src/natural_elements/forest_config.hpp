#pragma once
#include <cstdint> // for std::uint8_t, std::uint32_t
#include "color_palettes/color_structs.hpp" // for kColorRampSize

namespace liminal {

struct ForestConfig {
    std::uint32_t seed = 42; // Seed for tree placement, sizes and colors
    // Area in which trees are placed (pixels, y measured from the top of the scene)
    float minX = 50.0f;
    float maxX = 750.0f;
    float minY = 460.0f;
    float maxY = 580.0f;
    float density = 0.0005f; // Trees per pixel² of the area (halved, see Forest constructor)
    float minScale = 0.5f; // Smallest tree scale
    float maxScale = 1.5f; // Largest tree scale
    std::uint8_t minColorIndex = 0; // Minimum color index for crowns and trunks
    std::uint8_t maxColorIndex = kColorRampSize - 1; // Maximum color index for crowns and trunks
};

} // namespace liminal
