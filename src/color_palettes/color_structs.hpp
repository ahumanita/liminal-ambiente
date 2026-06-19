#pragma once
#include <array>
#include <raylib.h>

namespace liminal {

struct ColorGradient {
    std::array<Color, 2> colors;
};

struct ColorLayers {
    std::array<Color, 3> colors;
};

struct ColorRamp {
    std::array<Color, 8> colors;
};

} // namespace liminal