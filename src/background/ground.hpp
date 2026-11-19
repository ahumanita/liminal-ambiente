#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"
#include "ground_config.hpp"

namespace liminal {

class Ground {
public:
    Ground(const GroundConfig& config = GroundConfig()) noexcept;
    
    float getHeight() const {return config.height;}

private:
    GroundConfig config;
};

} // namespace liminal