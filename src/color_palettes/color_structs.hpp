#pragma once
#include <array>
#include <cmath>
#include <algorithm>
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

/**
 * Linearly interpolate between two colors a and b by factor f (0.0 to 1.0).
 * 
 * @param a The first color (when f=0.0)
 * @param b The second color (when f=1.0)
 * @param f The interpolation factor (0.0 to 1.0)
 * @return The interpolated color
 */
inline Color lerpColor(const Color &a, const Color &b, float f) noexcept {
    auto mix = [f](unsigned char x, unsigned char y) -> unsigned char {
        int v = static_cast<int>(std::lround((1.0f - f) * x + f * y));
        v = std::clamp(v, 0, 255);
        return static_cast<unsigned char>(v);
    };
    return Color{ mix(a.r, b.r), mix(a.g, b.g), mix(a.b, b.b), mix(a.a, b.a) };
};


/**
 * Linearly interpolate each color contained in two instances of the ColorStruct type.
 * 
 * @param r1 The first ColorStruct (when f=0.0)
 * @param r2 The second ColorStruct (when f=1.0)
 * @param f The interpolation factor (0.0 to 1.0)
 * @return A new ColorStruct with each color interpolated between r1 and r2 by
 */
template <class ColorStruct>
ColorStruct lerpColorStruct(const ColorStruct &r1, const ColorStruct &r2, float f) noexcept {
    ColorStruct out;
    for (size_t i = 0; i < out.colors.size(); ++i) {
        out.colors[i] = lerpColor(r1.colors[i], r2.colors[i], f);
    }
    return out;
};

} // namespace liminal