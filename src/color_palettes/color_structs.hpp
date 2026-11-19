#pragma once
#include <array>
#include <cmath>
#include <algorithm>
#include <raylib.h>

namespace liminal {

struct ColorGradient {
    std::array<Color, 2> colors;
};

struct ColorBounds {
    std::array<Color, 2> colors;
};

// Number of colors in a ColorRamp (deep shadow ... fog-tinted). Single source of truth
// for the ramp size: configs derive their valid color index range from it.
inline constexpr std::size_t kColorRampSize = 8;

struct ColorRamp {
    std::array<Color, kColorRampSize> colors;
};

/**
 * Linearly interpolate between two colors a and b by factor f (0.0 to 1.0).
 * 
 * @param a The first color (when f=0.0)
 * @param b The second color (when f=1.0)
 * @param f The interpolation factor (0.0 to 1.0)
 * @return The interpolated color
 */
inline Color lerpColor(const Color &a, const Color &b, float factor) noexcept {
    auto mix = [factor](unsigned char x, unsigned char y) -> unsigned char {
        int v = static_cast<int>(std::lround((1.0f - factor) * x + factor * y));
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
ColorStruct lerpColorStruct(const ColorStruct &r1, const ColorStruct &r2, float factor) noexcept {
    ColorStruct out;
    for (size_t i = 0; i < out.colors.size(); ++i) {
        out.colors[i] = lerpColor(r1.colors[i], r2.colors[i], factor);
    }
    return out;
};

} // namespace liminal