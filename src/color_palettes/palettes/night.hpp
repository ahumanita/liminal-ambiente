#include "color_palettes/scene_palette.hpp"
#include <raylib.h>

class NightPalette : public ScenePalette {
public:
    NightPalette() {
        skyGradient.colors = {
            Color{3, 8, 25, 255},    // Midnight navy
            Color{10, 25, 50, 255}   // Deep twilight
        };
        groundGradient.colors = {
            Color{6, 12, 8, 255},     // Very dark desaturated green
            Color{14, 30, 18, 255}    // Muted ground green
        };
        forestCrownRamp.colors = {
            Color{15, 34, 21, 255},   // Dark desaturated green
            Color{12, 28, 18, 255},   // Deep muted green
            Color{20, 48, 24, 255},   // Cool forest green
            Color{28, 60, 30, 255},   // Slightly brighter leaf
            Color{18, 55, 22, 255},   // Night-shifted green
            Color{10, 40, 16, 255},   // Dim moss green
            Color{6, 30, 12, 255},    // Shadow green
            Color{30, 80, 35, 255}    // Subtle highlight
        };
        forestTrunkRamp.colors = {
            Color{40, 25, 15, 255},    // Deep bark
            Color{55, 35, 20, 255},    // Dark wood
            Color{70, 45, 25, 255},    // Muted brown
            Color{90, 60, 30, 255},    // Rich trunk tone
            Color{110, 75, 40, 255},   // Subtle mid-bark
            Color{130, 95, 55, 255},   // Warmer highlight
            Color{105, 80, 50, 255},   // Tan-ish
            Color{95, 70, 45, 255}     // Sandy shadow
        };
        rainRamp.colors = {
            Color{70, 110, 150, 220},  // Muted steel blue
            Color{60, 100, 140, 220},  // Cooler rain tone
            Color{45, 85, 130, 220},   // Deep rain
            Color{30, 70, 110, 220},   // Night rain
            Color{20, 55, 95, 200},    // Dim rain
            Color{10, 45, 85, 200},    // Subtle
            Color{5, 30, 70, 200},     // Near indigo
            Color{0, 10, 50, 200}      // Deepest night blue
        };
        fogRamp.colors = {
            Color{200, 210, 220, 160}, // Soft cool fog
            Color{180, 190, 200, 120},
            Color{160, 170, 180, 90},
            Color{140, 150, 160, 50},
            Color{120, 130, 140, 25},
            Color{100, 110, 120, 10},
            Color{80, 90, 100, 0},
            Color{80, 90, 100, 0}
        };
    }
};