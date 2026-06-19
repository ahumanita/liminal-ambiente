#include "mountains.hpp"
#include <iostream>

void createLayerRidgeLine(MountainLayer& layer, int numRidgePoints, float spread, int offset, int numRefinements) {
    std::vector<Vector2> ridgeLine;
    ridgeLine.reserve(numRidgePoints*numRefinements); // Reserve enough space for all refinements

    // Generate initial ridge line with random vertical offsets
    for (std::size_t i = 0; i < numRidgePoints; i++) {
        float x = i * spread;
        float y = layer.baseElevation + GetRandomValue(-layer.amplitude, layer.amplitude);
        ridgeLine.push_back({x, y});
    }

    // Refine the ridge line to create smoother mountains
    for (std::size_t r = 0; r < numRefinements; r++) {
        std::vector<Vector2> refined;
        refined.reserve(ridgeLine.size());
        for (std::size_t i = 0; i < ridgeLine.size() - 1; i++) {
            const Vector2& p1 = ridgeLine[i];
            const Vector2& p2 = ridgeLine[i + 1];
            // Add the original point
            refined.push_back(p1);
            // Add a midpoint with random vertical offset for more natural look
            float midX = (p1.x + p2.x) / 2.0f;
            float midY = (p1.y + p2.y) / 2.0f + GetRandomValue(-offset, offset); // Random offset for more jagged look
            refined.push_back({midX, midY});
        }
        // Add the last original point
        refined.push_back(ridgeLine.back()); 
        ridgeLine = refined;
        // Reduce offset for finer details in next refinement
        offset = offset * 0.5f; 
    }

    layer.ridgeLine = ridgeLine;
}

Mountains::Mountains(const WindowProperties& props, const ScenePalette& palette) : windowProps(props), numLayers(palette.mountainLayers.layers.size()) {
    // Get screen width
    int screenWidth = windowProps.width;
    // Compute horizontal spread factor based on number of segments
    float spread = static_cast<float>(screenWidth) / (numRidgePoints - 1);

    for(size_t i = 0; i < numLayers; i++) {
        MountainLayer layer;
        layer.baseElevation = windowProps.height - 200.0f - i * 100.0f; // Base elevation for each layer
        layer.amplitude = 50.0f + i * 20.0f; // Amplitude for height variation
        createLayerRidgeLine(layer, numRidgePoints, spread, 20, numRefinements);
        layers.push_back(layer);
    }
}

Mountains::~Mountains() {}

void Mountains::draw(const ScenePalette& palette) {
    // Draw layers from back to front, note that layer_idx starts at layers.size()-1
    for (size_t layer_idx = layers.size(); layer_idx-- > 0 ;) {
        // Use corresponding color from palette for each layer
        Color color = palette.mountainLayers.layers[layer_idx];
        for (std::size_t j = 0; j < layers[layer_idx].ridgeLine.size() - 1; j++)
        {
            // Get the top vertices of the current mountain segment
            const Vector2& leftTop  = layers[layer_idx].ridgeLine[j];
            const Vector2& rightTop = layers[layer_idx].ridgeLine[j + 1];
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