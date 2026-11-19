#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"
#include "rain_config.hpp"
#include "procedural/random.hpp"

namespace liminal {

class RainDrop : public NaturalElement {
public:
    RainDrop(float x, float y, float len, float speed, uint8_t colorIndex);
    void update(float dt) override;
    void reset(float newX);

    float getLength() const {return len;}

private:
    float len;
    float speed;
};

class RainSystem {
public:
    RainSystem(int screenW, int screenH, const RainConfig& rainConfig = RainConfig());
    void update(float dt);
    void setIntensity(float newIntensity);
    float getIntensity() const { return config.intensity; }

    const std::vector<RainDrop>& getRainDrops() const {return drops;}

private:
    std::vector<RainDrop> drops;
    int width;
    int height;
    RainConfig config;
    Rng rng; // Declared after config: members are initialized in declaration order, and rng is seeded from config
};

} // namespace liminal
