#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"

namespace liminal {

class Ground {
public:
    Ground(float height) noexcept;
    void draw(const ScenePalette &palette) const noexcept;

private:
    float height;
};

} // namespace liminal