#pragma once
#include "color_palettes/scene_palette.hpp"
#include <raylib.h>

class DayPalette : public ScenePalette {
public:
    DayPalette() {
        mountainLayers.colors = {
            Color{78, 80, 85, 255},   // Near rough gray
            Color{98, 108, 125, 255}, // Mid muted blue-gray
            Color{124, 140, 170, 255} // Far softened blue haze
        };
        skyGradient.colors = {
            Color{135, 206, 235, 255}, // SkyBlue
            Color{80, 160, 235, 255}
        };

        groundGradient.colors = {
            Color{34, 139, 34, 255},   // ForestGreen
            Color{160, 255, 160, 255}
        };

        forestCrownRamp.colors = {
            Color{44, 102, 36, 255},
            Color{60, 122, 45, 255},
            Color{80, 150, 55, 255},
            Color{100, 170, 70, 255},
            Color{120, 190, 85, 255},
            Color{140, 205, 100, 255},
            Color{160, 220, 120, 255},
            Color{180, 240, 140, 255}
        };

        forestTrunkRamp.colors = {
            Color{80, 50, 30, 255},
            Color{100, 60, 35, 255},
            Color{120, 75, 45, 255},
            Color{140, 90, 55, 255},
            Color{160, 110, 70, 255},
            Color{180, 130, 85, 255},
            Color{200, 150, 100, 255},
            Color{220, 170, 120, 255}
        };

        rainRamp.colors = {
            Color{180, 210, 235, 230},
            Color{160, 200, 225, 230},
            Color{140, 190, 215, 220},
            Color{120, 180, 205, 210},
            Color{100, 165, 190, 200},
            Color{80, 150, 170, 190},
            Color{60, 130, 150, 180},
            Color{40, 110, 130, 170}
        };

        fogRamp.colors = {
            Color{255, 255, 255, 200},
            Color{250, 250, 250, 160},
            Color{240, 240, 240, 120},
            Color{220, 220, 220, 80},
            Color{200, 200, 200, 40},
            Color{180, 180, 180, 20},
            Color{160, 160, 160, 0},
            Color{160, 160, 160, 0}
        };
    }
};
