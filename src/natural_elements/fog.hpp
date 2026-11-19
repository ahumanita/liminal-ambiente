#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"
#include "fog_config.hpp"

namespace liminal {

class Fog : public NaturalElement {
public:
    Fog(const FogConfig& fogConfig = FogConfig());
    void update(float dt) override;

    float getWidth() const {return config.width;}
    float getHeight() const {return config.height;}
    float getSpeed() const {return config.speed;}
    float getAlpha() const {return config.density;}

    void setSpeed(float newSpeed);
    void setAlpha(float newAlpha);

private:
    FogConfig config;
};

} // namespace liminal
