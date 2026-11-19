#pragma once
#include <vector>
#include <raylib.h>
#include "color_palettes/scene_palette.hpp"
#include "sky_config.hpp"

namespace liminal {

class Sky {
public:
    Sky(const SkyConfig& config = SkyConfig()) noexcept;

    float getStartHeight() const {return config.startHeight;}

private:
    SkyConfig config;
};

} // namespace liminal