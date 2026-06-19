#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"

namespace liminal {

class RainDrop : public NaturalElement<RainDrop> {
public:
    RainDrop(float x, float y, float len, float speed, uint8_t colorIndex);
    void update(float dt) override;
    void draw(const ScenePalette& palette) const override;

    void reset(int width);

private:
    float len;
    float speed;
};

class RainSystem {
public:
    RainSystem(int count, int screenW, int screenH);
    void update(float dt);
    void draw(const ScenePalette& palette) const;

private:
    std::vector<RainDrop> drops;
    int width;
    int height;
};

} // namespace liminal
