#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"

namespace liminal {

class Sky {
public:
    Sky(float start_height) noexcept;

    float getStartHeight() const {return start_height;}

private:
    float start_height;
};

} // namespace liminal