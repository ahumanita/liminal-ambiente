#pragma once
#include "color_palettes/scene_palette.hpp"
#include <raylib.h>

class DawnPalette : public ScenePalette {
public:
    DawnPalette() {
        mountainLayers.colors = {
            Color{55, 60, 65, 255},   // Near dawn gray
            Color{82, 95, 115, 255},  // Mid cool morning
            Color{108, 130, 155, 255} // Far blue-hinted haze
        };
        skyGradient.colors = {
            Color{255, 153, 102, 255}, // Soft peach
            Color{110, 170, 210, 255}  // Morning blue
        };

        groundGradient.colors = {
            Color{50, 90, 40, 255},   // Dim green
            Color{150, 205, 130, 255}
        };

        forestCrownRamp.colors = {
            Color{40, 90, 36, 255},
            Color{55, 110, 45, 255},
            Color{70, 130, 55, 255},
            Color{95, 150, 70, 255},
            Color{110, 170, 80, 255},
            Color{130, 190, 95, 255},
            Color{150, 205, 110, 255},
            Color{170, 220, 130, 255}
        };

        forestTrunkRamp.colors = {
            Color{50, 30, 18, 255},
            Color{80, 45, 25, 255},
            Color{100, 60, 35, 255},
            Color{130, 80, 50, 255},
            Color{160, 100, 60, 255},
            Color{190, 120, 80, 255},
            Color{210, 145, 100, 255},
            Color{230, 160, 120, 255}
        };

        rainRamp.colors = {
            Color{140, 180, 210, 220},
            Color{120, 165, 200, 220},
            Color{100, 150, 190, 220},
            Color{90, 135, 175, 200},
            Color{70, 120, 160, 180},
            Color{60, 105, 140, 180},
            Color{50, 90, 120, 160},
            Color{40, 70, 100, 140}
        };

        fogRamp.colors = {
            Color{255, 255, 255, 200},
            Color{255, 250, 245, 160},
            Color{240, 240, 235, 120},
            Color{220, 220, 215, 80},
            Color{200, 200, 195, 40},
            Color{180, 180, 175, 20},
            Color{160, 160, 155, 0},
            Color{160, 160, 155, 0}
        };
    }
};
