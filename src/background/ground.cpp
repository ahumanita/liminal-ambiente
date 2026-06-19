#include "ground.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

Ground::Ground(float height)
    : height(height) {}

void Ground::draw(const ScenePalette &palette) const {
    // Create a rectangle with a color gradient that is in the background
    for (int y = 0; y < height; ++y) {
        float t = static_cast<float>(y) / height;
        Color blendedColor = lerpColor(palette.groundGradient.colors[0], palette.groundGradient.colors[1], t);
        DrawLine(0, GetScreenHeight() - height + y, GetScreenWidth(), GetScreenHeight() - height + y, blendedColor);
    }
}

} // namespace liminal