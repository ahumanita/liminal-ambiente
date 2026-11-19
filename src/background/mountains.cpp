#include "mountains.hpp"
#include "procedural/random.hpp"

#include <cmath>
#include <iostream>
#include <utility>

namespace liminal {

void createLayerRidgeLine(MountainLayer& layer, std::size_t numRidgePoints, float spread, float midpointDisplacement, std::size_t numRefinements, float roughness, Rng& rng) {
    std::vector<Vector2> ridgeLine;
    ridgeLine.reserve(numRidgePoints);

    // Generate initial ridge line with random vertical offsets
    for (std::size_t pointIndex = 0; pointIndex < numRidgePoints; ++pointIndex) {
        float x = pointIndex * spread;
        float y = layer.elevation + randomFloat(rng, -layer.amplitude, layer.amplitude);
        ridgeLine.push_back({x, y});
    }

    // Refine the ridge line to create smoother mountains
    for (std::size_t refinementPass = 0; refinementPass < numRefinements; ++refinementPass) {
        std::vector<Vector2> refined;
        // Each pass inserts one midpoint per segment: n points -> n + (n - 1) = 2n - 1
        refined.reserve(2 * ridgeLine.size() - 1);
        for (std::size_t segmentIndex = 0; segmentIndex < ridgeLine.size() - 1; ++segmentIndex) {
            const Vector2& p1 = ridgeLine[segmentIndex];
            const Vector2& p2 = ridgeLine[segmentIndex + 1];
            // Add the original point
            refined.push_back(p1);
            // Add a midpoint with random vertical offset for more natural look
            float midX = (p1.x + p2.x) / 2.0f;
            float midY = (p1.y + p2.y) / 2.0f + randomFloat(rng, -midpointDisplacement, midpointDisplacement); // Random offset for more jagged look
            refined.push_back({midX, midY});
        }
        // Add the last original point
        refined.push_back(ridgeLine.back()); 
        // Move instead of copy: ridgeLine takes over refined's buffer, nothing is duplicated
        ridgeLine = std::move(refined);
        // Reduce offset for finer details in next refinement
        midpointDisplacement = midpointDisplacement * roughness; 
    }

    layer.ridgeLine = std::move(ridgeLine);
}

Mountains::Mountains(const SceneSize& size, const MountainConfig& mountainConfig) : sceneSize(size), config(mountainConfig) {
    if (config.numLayers <= 1 || config.numRidgePoints < 2) {
        std::cerr << "Invalid mountain configuration: numLayers must be > 1 and numRidgePoints must be >= 2." << std::endl;
        return;
    }
    if (config.numRefinements > 10) {
        // Write warning that numRefinements gets capped to 10
        std::cerr << "Warning: numRefinements is too high, capping to 10 for performance reasons." << std::endl;
        config.numRefinements = 10;
    }
    
    // Compute horizontal spread factor based on number of segments, across the scene (not the window)
    float spread = sceneSize.width / (config.numRidgePoints - 1);

    // One generator for all layers, seeded from the config, so the same config always
    // gives the same mountains. It is passed on by reference: a copy per layer would
    // replay the same sequence, and every layer would get the same ridge shape.
    Rng rng(config.seed);

    for(size_t layerIndex = 0; layerIndex < config.numLayers; ++layerIndex) {
        float t = layerIndex / float(config.numLayers - 1); // Normalize layer index
        MountainLayer layer;
        layer.depth = t; // Assign depth for parallax effect
        layer.elevation = sceneSize.height - std::lerp(config.nearElevation, config.farElevation, t); // Interpolate elevation between near and far
        layer.amplitude = std::lerp(config.nearAmplitude, config.farAmplitude, t); // Interpolate amplitude between near and far
        createLayerRidgeLine(layer, config.numRidgePoints, spread, config.midpointDisplacement, config.numRefinements, config.roughness, rng);
        layers.push_back(layer);
    }
}

Mountains::~Mountains() {}

} // namespace liminal