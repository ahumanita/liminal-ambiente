#include "mountains.hpp"

Mountains::Mountains(WindowProperties* props) : windowProps(props) {
    // Complete screen width is
    int screenWidth = windowProps->width;
    float spread = static_cast<float>(screenWidth) / (numRidgePoints - 1); // Number of segments
    // Create random control points with random height values
    ridgeLine.reserve(numRidgePoints);
    for (int i = 0; i < numRidgePoints; i++) {
        float x = i * spread; // Spread control points across the width
        float y = 250.0f + GetRandomValue(-100, 100); // Random height around 300
        ridgeLine.push_back({x, y});
    }

    // return;
    // Refine the ridge line to create smoother mountains
    int offset = 20; // Max vertical offset for midpoints to create more jagged look
    for (int r = 0; r < numRefinements; r++) {
        std::vector<Vector2> refined;
        refined.reserve(ridgeLine.size() * 2 - 1);
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
}

Mountains::~Mountains() {}

void Mountains::draw(ScenePalette& palette) {

    Color color = palette.mountainLayers.layers[0]; // Near layer color
    
    for (std::size_t i = 0; i < ridgeLine.size() - 1; ++i)
    {
        // Get the top vertices of the current mountain segment
        const Vector2& leftTop  = ridgeLine[i];
        const Vector2& rightTop = ridgeLine[i + 1];
        // Define corresponding bottom vertices at the bottom of the screen
        Vector2 leftBottom{
            leftTop.x,
            static_cast<float>(windowProps->height)
        };
        Vector2 rightBottom{
            rightTop.x,
            static_cast<float>(windowProps->height)
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