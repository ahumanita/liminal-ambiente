#include "color_palettes/scene_palette.hpp"
#include <raylib.h>

class DuskPalette : public ScenePalette {
public:
    DuskPalette() {
        skyGradient.colors = {
            Color{255, 94, 77, 255},   // Light Red
            Color{255, 0, 0, 255}      // Red
        };
        groundGradient.colors = {
            Color{0, 100, 0, 255},     // Dark Green
            Color{34, 139, 34, 255}    // Forest Green
        };
        forestCrownRamp.colors = {
            Color{85, 107, 47, 255},   // DarkOliveGreen
            Color{107, 142, 35, 255},  // OliveDrab
            Color{154, 205, 50, 255},  // YellowGreen
            Color{50, 205, 50, 255},   // LimeGreen
            Color{0, 255, 0, 255},     // Lime
            Color{124, 252, 0, 255},   // LawnGreen
            Color{127, 255, 0, 255},   // Chartreuse
            Color{173, 255, 47, 255}   // GreenYellow
        };
        forestTrunkRamp.colors = {
            Color{101, 67, 33, 255},   // Brown
            Color{139, 69, 19, 255},   // SaddleBrown
            Color{160, 82, 45, 255},   // Sienna
            Color{205, 133, 63, 255},  // Peru
            Color{222, 184, 135, 255}, // BurlyWood
            Color{245, 222, 179, 255}, // Wheat
            Color{210, 180, 140, 255}, // Tan
            Color{244, 164, 96, 255}   // SandyBrown
        };
        rainRamp.colors = {
            Color{173, 216, 230, 255}, // LightBlue
            Color{135, 206, 235, 255}, // SkyBlue
            Color{0, 191, 255, 255},   // DeepSkyBlue
            Color{30, 144, 255, 255},  // DodgerBlue
            Color{70, 130, 180, 255},  // SteelBlue
            Color{100, 149, 237, 255}, // CornflowerBlue
            Color{65, 105, 225, 255},  // RoyalBlue
            Color{0, 0, 255, 255}      // Blue
        };
        fogRamp.colors = {
            Color{255, 255, 255, 200}, // White with some transparency
            Color{255, 255, 255, 150},
            Color{255, 255, 255, 100},
            Color{255, 255, 255, 50},
            Color{255, 255, 255, 25},
            Color{255, 255, 255, 10},
            Color{255, 255, 255, 0},
            Color{255, 255, 255, 0}
        };
    }
};