#include <vector>
#include <cmath>

#include "color_palettes/scene_palette.hpp"
#include "color_palettes/palettes/dusk.hpp"
#include "color_palettes/palettes/night.hpp"
#include "color_palettes/palettes/dawn.hpp"
#include "color_palettes/palettes/day.hpp"
#include "color_palettes/environment_state.hpp"

namespace liminal {

/**
 * Linearly interpolate between two colors a and b by factor f (0.0 to 1.0).
 * 
 * @param a The first color (when f=0.0)
 * @param b The second color (when f=1.0)
 * @param f The interpolation factor (0.0 to 1.0)
 * @return The interpolated color
 */
Color lerpColor(const Color &a, const Color &b, float f) {
    auto mix = [f](unsigned char x, unsigned char y) -> unsigned char {
        int v = static_cast<int>(std::lround((1.0f - f) * x + f * y));
        if (v < 0) v = 0; if (v > 255) v = 255; return static_cast<unsigned char>(v);
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
ColorStruct lerpColorStruct(const ColorStruct &r1, const ColorStruct &r2, float f) {
    ColorStruct out;
    for (size_t i = 0; i < out.colors.size(); ++i) {
        out.colors[i] = lerpColor(r1.colors[i], r2.colors[i], f);
    }
    return out;
};


class PaletteManager {
public:
    PaletteManager() {
        palettes.push_back(NightPalette());        
        palettes.push_back(DawnPalette());
        palettes.push_back(DayPalette());
        palettes.push_back(DuskPalette());
    }

    // Compute an interpolated ScenePalette for the given environment state.
    // Returns by value (cheap-ish small structs) to avoid dangling references.
    ScenePalette computeCurrentPalette(const EnvironmentState &environmentState) const {
        if (palettes.empty()) return ScenePalette();

        // Map timeOfDay [0,1) across the palette list circularly.
        float t = environmentState.timeOfDay;
        float scaled = t * static_cast<float>(palettes.size());
        int idx = static_cast<int>(std::floor(scaled)) % static_cast<int>(palettes.size());
        // Ensure that the current palette index is between 0 and 3
        if (idx < 0) idx += static_cast<int>(palettes.size());
        int next = (idx + 1) % static_cast<int>(palettes.size());
        float localT = scaled - std::floor(scaled);

        const ScenePalette &A = palettes[idx];
        const ScenePalette &B = palettes[next];

        ScenePalette result;
        result.mountainLayers = lerpColorStruct<ColorLayers>(A.mountainLayers, B.mountainLayers, localT);
        result.skyGradient = lerpColorStruct<ColorGradient>(A.skyGradient, B.skyGradient, localT);
        result.groundGradient = lerpColorStruct<ColorGradient>(A.groundGradient, B.groundGradient, localT);
        result.forestCrownRamp = lerpColorStruct<ColorRamp>(A.forestCrownRamp, B.forestCrownRamp, localT);
        result.forestTrunkRamp = lerpColorStruct<ColorRamp>(A.forestTrunkRamp, B.forestTrunkRamp, localT);
        result.fogRamp = lerpColorStruct<ColorRamp>(A.fogRamp, B.fogRamp, localT);
        result.rainRamp = lerpColorStruct<ColorRamp>(A.rainRamp, B.rainRamp, localT);

        return result;
    }

private:
    std::vector<ScenePalette> palettes;
};

} // namespace liminal