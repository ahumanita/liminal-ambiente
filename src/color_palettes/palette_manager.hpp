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
        float timeOfDayNorm = std::clamp(environmentState.timeOfDay, 0.0f, 1.0f);
        float scaledTime = timeOfDayNorm * static_cast<float>(palettes.size());
        int currentIndex = static_cast<int>(std::floor(scaledTime)) % static_cast<int>(palettes.size());
        // Ensure that the current palette index is between 0 and 3
        if (currentIndex < 0) currentIndex += static_cast<int>(palettes.size());
        int nextIndex = (currentIndex + 1) % static_cast<int>(palettes.size());
        float localFactor = std::clamp(scaledTime - std::floor(scaledTime), 0.0f, 1.0f);

        const ScenePalette &A = palettes[currentIndex];
        const ScenePalette &B = palettes[nextIndex];

        ScenePalette result;
        result.mountainLayers = lerpColorStruct<ColorLayers>(A.mountainLayers, B.mountainLayers, localFactor);
        result.skyGradient = lerpColorStruct<ColorGradient>(A.skyGradient, B.skyGradient, localFactor);
        result.groundGradient = lerpColorStruct<ColorGradient>(A.groundGradient, B.groundGradient, localFactor);
        result.forestCrownRamp = lerpColorStruct<ColorRamp>(A.forestCrownRamp, B.forestCrownRamp, localFactor);
        result.forestTrunkRamp = lerpColorStruct<ColorRamp>(A.forestTrunkRamp, B.forestTrunkRamp, localFactor);
        result.fogRamp = lerpColorStruct<ColorRamp>(A.fogRamp, B.fogRamp, localFactor);
        result.rainRamp = lerpColorStruct<ColorRamp>(A.rainRamp, B.rainRamp, localFactor);

        return result;
    }

private:
    std::vector<ScenePalette> palettes;
};

} // namespace liminal