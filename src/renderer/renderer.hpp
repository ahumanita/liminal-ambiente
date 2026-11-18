#pragma once

#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"
#include "background/mountains.hpp"
#include "color_palettes/scene_palette.hpp"
#include "gui/window_properties.hpp"

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
    void render(const Scene& scene, const ScenePalette& palette) const noexcept;

private:
    const WindowProperties& windowProps;
};

} // namespace liminal
