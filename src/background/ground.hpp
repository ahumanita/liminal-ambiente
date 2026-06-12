#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"

class Ground {
public:
    Ground(float height);
    void draw(const ScenePalette &palette) const;

private:
    float height;
};