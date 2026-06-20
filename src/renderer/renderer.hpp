#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"
#include "background/mountains.hpp"

namespace liminal {

struct Scene {
    const Mountains& mountains;
    const Sky& sky;
    const Ground& ground;
    const RainSystem& rain;
    const Forest& forest;
    const Fog& fog;

    Scene(const Mountains& m, const Sky& s, const Ground& g, const RainSystem& r, const Forest& f, const Fog& fog) : mountains(m), sky(s), ground(g), rain(r), forest(f), fog(fog) {}
};

class Renderer {
public:
    Renderer(const WindowProperties& props) : windowProps(props) {};
    void drawMountains(const Mountains& mountains, const ScenePalette& palette) const noexcept;
    void drawSky(const Sky& sky, const ScenePalette& palette) const noexcept;
    void drawGround(const Ground& ground, const ScenePalette& palette) const noexcept;
    void drawForest(const Forest& forest, const ScenePalette& palette) const noexcept;
    void drawRainSystem(const RainSystem& rain, const ScenePalette& palette) const noexcept;
    void drawFog(const Fog& fog, const ScenePalette& palette) const noexcept;
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

void Renderer::drawRainSystem(const RainSystem& rain, const ScenePalette& palette) const noexcept {
    const auto drops = rain.getRainDrops();
    for (const auto &rain_drop : drops) {
        const auto position = rain_drop.getPosition();
        const auto length = rain_drop.getLength();
        const auto paletteIndex = rain_drop.getColorPaletteIndex();

        Vector2 start = { position.x, position.y };
        Vector2 end = { position.x, position.y + length };
        Color dropColor = getColorFromRamp(palette.rainRamp, paletteIndex);
        DrawLineEx(start, end, 1.0f, dropColor);
    }
}

void Renderer::drawForest(const Forest& forest, const ScenePalette& palette) const noexcept {
    const auto trees = forest.getTrees();
    for (const auto &tree : trees) {
        // Get data
        const auto position = tree.getPosition();
        const auto scale = tree.getScale();
        const auto trunkPaleteIndex = tree.getTrunkColorIndex();
        const auto crownPaletteIndex = tree.getColorPaletteIndex();
        // Trunk
        int trunkW = static_cast<int>(16 * scale);
        int trunkH = static_cast<int>(40 * scale);
        // Draw trunk with a brown color and and scale brightness based on the shadeFactor
        Color trunkColor = getColorFromRamp(palette.forestTrunkRamp, trunkPaleteIndex);
        DrawRectangle(
            static_cast<int>(position.x - trunkW / 2),
            static_cast<int>(position.y),
            trunkW,
            trunkH,
            trunkColor
        );

        // Draw crown color with the specified foliage color and scale brightness based on a 
        // the shadeFactor
        Color crownColor = getColorFromRamp(palette.forestCrownRamp, crownPaletteIndex);
        
        int s1 = static_cast<int>(80 * scale);
        int s2 = static_cast<int>(56 * scale);
        int s3 = static_cast<int>(40 * scale);

        Vector2 b1[3] = {
            {position.x - s1 / 2.0f, position.y},
            {position.x + s1 / 2.0f, position.y},
            {position.x, position.y - 48.0f * scale}
        };
        DrawTriangle(b1[0], b1[1], b1[2], crownColor);

        Vector2 b2[3] = {
            {position.x - s2 / 2.0f, position.y - 28.0f * scale},
            {position.x + s2 / 2.0f, position.y - 28.0f * scale},
            {position.x, position.y - 80.0f * scale}
        };
        DrawTriangle(b2[0], b2[1], b2[2], crownColor);

        Vector2 b3[3] = {
            {position.x - s3 / 2.0f, position.y - 52.0f * scale},
            {position.x + s3 / 2.0f, position.y - 52.0f * scale},
            {position.x, position.y - 108.0f * scale}
        };
        DrawTriangle(b3[0], b3[1], b3[2], crownColor);
    }
}

void Renderer::drawFog(const Fog& fog, const ScenePalette& palette) const noexcept {
    const auto colorPaletteIndex = fog.getColorPaletteIndex();
    const auto position = fog.getPosition();
    const auto width = fog.getWidth();
    const auto height = fog.getHeight();

    Color color = getColorFromRamp(palette.fogRamp, colorPaletteIndex);
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), color);
}

void Renderer::render(const Scene scene, const ScenePalette& palette) const noexcept {
    // Draw the background
    drawSky(scene.sky, palette);
    drawMountains(scene.mountains, palette);
    drawGround(scene.ground, palette);
    // Draw the natural elements
    drawForest(scene.forest, palette);
    drawRainSystem(scene.rain, palette);
    drawFog(scene.fog, palette);
}

} // namespace liminal
