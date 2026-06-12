#pragma once
#include "color_ramp.hpp"
#include "color_gradient.hpp"
#include <cstdint>

struct ScenePalette {
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