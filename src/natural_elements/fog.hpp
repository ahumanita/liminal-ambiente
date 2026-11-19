#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"
#include "fog_config.hpp"

namespace liminal {

class Fog : public NaturalElement {
public:
    Fog(const FogConfig& fogConfig = FogConfig());
    void update(float dt, const EnvironmentState& env) override;

    float getWidth() const {return config.width;}
    float getHeight() const {return config.height;}

private:
    FogConfig config;
};

} // namespace liminal
