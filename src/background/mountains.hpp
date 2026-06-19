#pragma once

#include <raylib.h>
#include <vector>

#include "color_palettes/scene_palette.hpp"
#include "gui/window_properties.hpp"

namespace liminal {

struct MountainLayer {
    float baseElevation;
    float amplitude;
    std::vector<Vector2> ridgeLine;
};

class Mountains {
public:
    Mountains(const WindowProperties& props, const ScenePalette& palette);
    ~Mountains();

    void draw(const ScenePalette& palette) const noexcept;

private:
    const WindowProperties& windowProps; // To access screen dimensions for drawing
    int numRidgePoints = 8; // Number of control points for the ridge line
    int numRefinements = 3; // Number of times to refine the ridge line for smoother mountains
    int numLayers;          // Number of mountain layers (based on palette)
    std::vector<MountainLayer> layers; // Store properties for each mountain layer
};

} // namespace liminal