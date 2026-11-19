#pragma once

#include <raylib.h>
#include <vector>

#include "color_palettes/scene_palette.hpp"
#include "scene/scene_size.hpp"
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
    Mountains(const SceneSize& sceneSize, const MountainConfig& mountainConfig = MountainConfig());
    ~Mountains();

    const std::vector<MountainLayer>& getLayers() const { return layers; }

private:
    SceneSize sceneSize; // Scene dimensions the ridge lines are generated for (a copy, so no lifetime assumptions)
    MountainConfig config;  // Configuration for mountain generation
    std::vector<MountainLayer> layers; // Store properties for each mountain layer
};

} // namespace liminal