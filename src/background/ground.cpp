#include "ground.hpp"
#include <raylib.h>
#include <cstdlib>

Ground::Ground(float height)
    : height(height) {}

void Ground::draw(const ScenePalette &palette) const {
    // Create a rectangle with a color gradient that is in the background
    for (int y = 0; y < height; ++y) {
        float t = static_cast<float>(y) / height;
        Color blendedColor = {
            static_cast<unsigned char>(palette.groundGradient.colors[0].r * t + palette.groundGradient.colors[1].r * (1 - t)),
            static_cast<unsigned char>(palette.groundGradient.colors[0].g * t + palette.groundGradient.colors[1].g * (1 - t)),
            static_cast<unsigned char>(palette.groundGradient.colors[0].b * t + palette.groundGradient.colors[1].b * (1 - t)),
            255
        };
        DrawLine(0, GetScreenHeight() - height + y, GetScreenWidth(), GetScreenHeight() - height + y, blendedColor);
    }
}