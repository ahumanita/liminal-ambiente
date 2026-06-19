#pragma once
#include "color_palettes/scene_palette.hpp"
#include "color_palettes/palettes/dusk.hpp"
#include "color_palettes/palettes/night.hpp"
#include "color_palettes/palettes/dawn.hpp"
#include "color_palettes/palettes/day.hpp"
#include "color_palettes/environment_state.hpp"

namespace liminal {

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
        float t = std::clamp(environmentState.timeOfDay, 0.0f, 1.0f);
        float scaled = t * static_cast<float>(palettes.size());
        int idx = static_cast<int>(std::floor(scaled)) % static_cast<int>(palettes.size());
        // Ensure that the current palette index is between 0 and 3
        if (idx < 0) idx += static_cast<int>(palettes.size());
        int next = (idx + 1) % static_cast<int>(palettes.size());
        float localT = std::clamp(scaled - std::floor(scaled), 0.0f, 1.0f);

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