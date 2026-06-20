#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"

namespace liminal {

class RainDrop : public NaturalElement {
public:
    RainDrop(float x, float y, float len, float speed, uint8_t colorIndex);
    void update(float dt) override;
    void reset(int width);

    float getLength() const {return len;}

private:
    float len;
    float speed;
};

class RainSystem {
public:
    RainSystem(int count, int screenW, int screenH);
    void update(float dt);

    std::vector<RainDrop> getRainDrops() const {return drops;}

private:
    std::vector<RainDrop> drops;
    int width;
    int height;
};

} // namespace liminal
