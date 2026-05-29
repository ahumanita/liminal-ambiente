#include "sky.hpp"
#include <raylib.h>
#include <cstdlib>

Sky::Sky(float start_height, Color color_bottom, Color color_top)
    : start_height(start_height), color_bottom(color_bottom), color_top(color_top) {}

void Sky::draw() const {
    // Create a rectangle with a color gradient that is in the background
    for (int y = 0; y < GetScreenHeight(); ++y) {
        float t = static_cast<float>(y) / GetScreenHeight();
        Color blendedColor = {
            static_cast<unsigned char>(color_bottom.r * t + color_top.r * (1 - t)),
            static_cast<unsigned char>(color_bottom.g * t + color_top.g * (1 - t)),
            static_cast<unsigned char>(color_bottom.b * t + color_top.b * (1 - t)),
            255
        };
        DrawLine(0, y, GetScreenWidth(), y, blendedColor);
    }
}