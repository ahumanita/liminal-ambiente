#pragma once
#include "color_structs.hpp"
#include <cstdint>

struct ScenePalette {
    ColorLayers mountainLayers;
    ColorGradient skyGradient;
    ColorGradient groundGradient;
    ColorRamp forestCrownRamp;
    ColorRamp forestTrunkRamp;
    ColorRamp fogRamp;
    ColorRamp rainRamp;
};

inline Color getColorFromRamp(const ColorRamp &ramp, uint8_t index) {
    return ramp.colors[index % ramp.colors.size()];
}