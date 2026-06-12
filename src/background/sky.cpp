#include "sky.hpp"
#include <raylib.h>
#include <cstdlib>

Sky::Sky(float start_height)
    : start_height(start_height) {}

void Sky::draw(const ScenePalette &palette) const {
    // Create a rectangle with a color gradient that is in the background
    for (int y = start_height; y < GetScreenHeight(); ++y) {
        float t = static_cast<float>(y) / GetScreenHeight();
        Color blendedColor = {
            static_cast<unsigned char>(palette.skyGradient.colors[0].r * t + palette.skyGradient.colors[1].r * (1 - t)),
            static_cast<unsigned char>(palette.skyGradient.colors[0].g * t + palette.skyGradient.colors[1].g * (1 - t)),
            static_cast<unsigned char>(palette.skyGradient.colors[0].b * t + palette.skyGradient.colors[1].b * (1 - t)),
            255
        };
        DrawLine(0, y, GetScreenWidth(), y, blendedColor);
    }
}