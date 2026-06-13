#include <vector>
#include <cmath>

#include "color_palettes/palettes/dusk.hpp"
#include "color_palettes/palettes/night.hpp"
#include "color_palettes/palettes/dawn.hpp"
#include "color_palettes/palettes/day.hpp"
#include "color_palettes/environment_state.hpp"

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
        if (idx < 0) idx += static_cast<int>(palettes.size());
        int next = (idx + 1) % static_cast<int>(palettes.size());
        float localT = scaled - std::floor(scaled);

        const ScenePalette &A = palettes[idx];
        const ScenePalette &B = palettes[next];

        auto lerpColor = [](const Color &a, const Color &b, float f) {
            auto mix = [f](unsigned char x, unsigned char y) -> unsigned char {
                int v = static_cast<int>(std::lround((1.0f - f) * x + f * y));
                if (v < 0) v = 0; if (v > 255) v = 255; return static_cast<unsigned char>(v);
            };
            return Color{ mix(a.r, b.r), mix(a.g, b.g), mix(a.b, b.b), mix(a.a, b.a) };
        };

        auto lerpGradient = [&](const ColorGradient &g1, const ColorGradient &g2, float f) {
            ColorGradient out;
            out.colors[0] = lerpColor(g1.colors[0], g2.colors[0], f);
            out.colors[1] = lerpColor(g1.colors[1], g2.colors[1], f);
            return out;
        };

        auto lerpLayers = [&](const ColorLayers &l1, const ColorLayers &l2, float f) {
            ColorLayers out;
            for (size_t i = 0; i < out.layers.size(); ++i) {
                out.layers[i] = lerpColor(l1.layers[i], l2.layers[i], f);
            }
            return out;
        };

        auto lerpRamp = [&](const ColorRamp &r1, const ColorRamp &r2, float f) {
            ColorRamp out;
            for (size_t i = 0; i < out.colors.size(); ++i) {
                out.colors[i] = lerpColor(r1.colors[i], r2.colors[i], f);
            }
            return out;
        };

        ScenePalette result;
        result.mountainLayers = lerpLayers(A.mountainLayers, B.mountainLayers, localT);
        result.skyGradient = lerpGradient(A.skyGradient, B.skyGradient, localT);
        result.groundGradient = lerpGradient(A.groundGradient, B.groundGradient, localT);
        result.forestCrownRamp = lerpRamp(A.forestCrownRamp, B.forestCrownRamp, localT);
        result.forestTrunkRamp = lerpRamp(A.forestTrunkRamp, B.forestTrunkRamp, localT);
        result.fogRamp = lerpRamp(A.fogRamp, B.fogRamp, localT);
        result.rainRamp = lerpRamp(A.rainRamp, B.rainRamp, localT);

        return result;
    }

private:
    std::vector<ScenePalette> palettes;
};