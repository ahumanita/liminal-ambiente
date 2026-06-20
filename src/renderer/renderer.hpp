#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"
#include "background/mountains.hpp"

namespace liminal {

struct Scene {
    Mountains mountains;
    Sky sky;
    Ground ground;

    Scene(const Mountains m, const Sky s, const Ground g) : mountains(m), sky(s), ground(g) {}
};

class Renderer {
public:
    Renderer(const WindowProperties& props) : windowProps(props) {};
    void drawMountains(const Mountains& mountains, const ScenePalette& palette) const noexcept;
    void drawSky(const Sky& sky, const ScenePalette& palette) const noexcept;
    void drawGround(const Ground& ground, const ScenePalette& palette) const noexcept;
    // void drawNaturalElements(const std::vector<NaturalElement*>& elements, const ScenePalette& palette) const noexcept;
    void render(const Scene scene, const ScenePalette& palette) const noexcept;

private:
    const WindowProperties& windowProps;
};

void Renderer::drawMountains(const Mountains& m, const ScenePalette& palette) const noexcept {
    const auto layers = m.getLayers();
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

void Renderer::drawSky(const Sky& s, const ScenePalette& palette) const noexcept {
    const auto start_height = s.getStartHeight();
    // Create a rectangle with a color gradient that is in the background
    for (int y = start_height; y < GetScreenHeight(); ++y) {
        float t = static_cast<float>(y) / GetScreenHeight();
        Color blendedColor = lerpColor(palette.skyGradient.colors[0], palette.skyGradient.colors[1], t);
        DrawLine(0, y, GetScreenWidth(), y, blendedColor);
    }
}

void Renderer::drawGround(const Ground& g, const ScenePalette& palette) const noexcept {
    const auto height = g.getHeight();
    // Create a rectangle with a color gradient that is in the background
    for (int y = 0; y < height; ++y) {
        float t = static_cast<float>(y) / height;
        Color blendedColor = lerpColor(palette.groundGradient.colors[0], palette.groundGradient.colors[1], t);
        DrawLine(0, GetScreenHeight() - height + y, GetScreenWidth(), GetScreenHeight() - height + y, blendedColor);
    }
}

void Renderer::render(const Scene scene, const ScenePalette& palette) const noexcept {
    // Draw the background
    drawSky(scene.sky, palette);
    drawMountains(scene.mountains, palette);
    drawGround(scene.ground, palette);
}

} // namespace liminal
