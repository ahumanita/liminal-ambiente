#include "sky.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

Sky::Sky(float start_height) noexcept
    : start_height(start_height) {}

void Sky::draw(const ScenePalette &palette) const noexcept {
    // Create a rectangle with a color gradient that is in the background
    for (int y = start_height; y < GetScreenHeight(); ++y) {
        float t = static_cast<float>(y) / GetScreenHeight();
        Color blendedColor = lerpColor(palette.skyGradient.colors[0], palette.skyGradient.colors[1], t);
        DrawLine(0, y, GetScreenWidth(), y, blendedColor);
    }
}

} // namespace liminal