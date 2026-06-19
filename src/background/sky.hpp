#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"

namespace liminal {

class Sky {
public:
    Sky(float start_height) noexcept;
    void draw(const ScenePalette &palette) const noexcept;

private:
    float start_height;
};

} // namespace liminal