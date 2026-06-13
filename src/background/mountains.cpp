#include "mountains.hpp"

Mountains::Mountains(WindowProperties* props) : windowProps(props) {
    // Complete screen width is
    int screenWidth = windowProps->width;
    float spread = static_cast<float>(screenWidth) / 9.0f; // 10 control points, so 9 segments
    // Create random control points with random height values
    ridgeLine.reserve(10);
    for (int i = 0; i < 10; i++) {
        float x = i * spread; // Spread control points across the width
        float y = 300.0f + GetRandomValue(-50, 50); // Random height around 300
        ridgeLine.push_back({x, y});
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