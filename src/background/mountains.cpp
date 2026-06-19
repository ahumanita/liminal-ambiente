#include "mountains.hpp"
#include <iostream>

namespace liminal {

void createLayerRidgeLine(MountainLayer& layer, int numRidgePoints, float spread, int verticalJitter, int numRefinements) {
    std::vector<Vector2> ridgeLine;
    ridgeLine.reserve(numRidgePoints*numRefinements); // Reserve enough space for all refinements

    // Generate initial ridge line with random vertical offsets
    for (std::size_t pointIndex = 0; pointIndex < numRidgePoints; ++pointIndex) {
        float x = pointIndex * spread;
        float y = layer.baseElevation + GetRandomValue(-layer.amplitude, layer.amplitude);
        ridgeLine.push_back({x, y});
    }

    // Refine the ridge line to create smoother mountains
    for (std::size_t refinementPass = 0; refinementPass < numRefinements; ++refinementPass) {
        std::vector<Vector2> refined;
        refined.reserve(ridgeLine.size());
        for (std::size_t segmentIndex = 0; segmentIndex < ridgeLine.size() - 1; ++segmentIndex) {
            const Vector2& p1 = ridgeLine[segmentIndex];
            const Vector2& p2 = ridgeLine[segmentIndex + 1];
            // Add the original point
            refined.push_back(p1);
            // Add a midpoint with random vertical offset for more natural look
            float midX = (p1.x + p2.x) / 2.0f;
            float midY = (p1.y + p2.y) / 2.0f + GetRandomValue(-verticalJitter, verticalJitter); // Random offset for more jagged look
            refined.push_back({midX, midY});
        }
        // Add the last original point
        refined.push_back(ridgeLine.back()); 
        ridgeLine = refined;
        // Reduce offset for finer details in next refinement
        verticalJitter = verticalJitter * 0.5f; 
    }

    layer.ridgeLine = ridgeLine;
}

Mountains::Mountains(const WindowProperties& props, const ScenePalette& palette) : windowProps(props), numLayers(palette.mountainLayers.colors.size()) {
    // Get screen width
    int screenWidth = windowProps.width;
    // Compute horizontal spread factor based on number of segments
    float spread = static_cast<float>(screenWidth) / (numRidgePoints - 1);

    for(size_t layerIndex = 0; layerIndex < numLayers; ++layerIndex) {
        MountainLayer layer;
        layer.baseElevation = windowProps.height - 200.0f - layerIndex * 100.0f; // Base elevation for each layer
        layer.amplitude = 50.0f + layerIndex * 20.0f; // Amplitude for height variation
        createLayerRidgeLine(layer, numRidgePoints, spread, 20, numRefinements);
        layers.push_back(layer);
    }
}

Mountains::~Mountains() {}

void Mountains::draw(const ScenePalette& palette) const noexcept {
    // Draw layers from back to front, note that layerIndex starts at layers.size()-1
    for (size_t layerIndex = layers.size(); layerIndex-- > 0 ;) {
        // Use corresponding color from palette for each layer
        Color color = palette.mountainLayers.colors[layerIndex];
        for (std::size_t segmentIdx = 0; segmentIdx < layers[layerIndex].ridgeLine.size() - 1; ++segmentIdx)
        {
            // Get the top vertices of the current mountain segment
            const Vector2& leftTop  = layers[layerIndex].ridgeLine[segmentIdx];
            const Vector2& rightTop = layers[layerIndex].ridgeLine[segmentIdx + 1];
            // Define corresponding bottom vertices at the bottom of the screen
            Vector2 leftBottom{
                leftTop.x,
                static_cast<float>(windowProps.height)
            };
            Vector2 rightBottom{
                rightTop.x,
                static_cast<float>(windowProps.height)
            };
            // Draw the mountain segment as two triangles
            DrawTriangle(
                leftTop,
                leftBottom,
                rightTop,
                color);
            DrawTriangle(
                rightTop,
                leftBottom,
                rightBottom,
                color);
        }
    }
}

} // namespace liminal