#pragma once
#include "color_ramp.hpp"
#include <cstdint>

struct ScenePalette {
    ColorRamp skyRamp;
    ColorRamp forestCrownRamp;
    ColorRamp forestTrunkRamp;
    ColorRamp fogRamp;
    ColorRamp rainRamp;
    ColorRamp grassRamp;
};

inline Color getColorFromRamp(const ColorRamp &ramp, uint8_t index) {
    return ramp.colors[index % ramp.colors.size()];
}