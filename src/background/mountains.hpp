#pragma once

#include <raylib.h>
#include <vector>

#include "color_palettes/scene_palette.hpp"
#include "gui/window_properties.hpp"
#include "mountain_config.hpp"

namespace liminal {

struct MountainLayer {
    float depth; // Depth of the layer, used for parallax effect
    float elevation; // Screen y-coordinate of the base of the mountain layer
    float amplitude;
    std::vector<Vector2> ridgeLine;
};

class Mountains {
public:
    Mountains(const WindowProperties& props, const MountainConfig& mountainConfig = MountainConfig());
    ~Mountains();

    const std::vector<MountainLayer>& getLayers() const { return layers; }

private:
    const WindowProperties& windowProps; // To access screen dimensions for drawing
    MountainConfig config;  // Configuration for mountain generation
    std::vector<MountainLayer> layers; // Store properties for each mountain layer
};

} // namespace liminal