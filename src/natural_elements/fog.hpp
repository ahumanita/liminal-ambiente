#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"

class Fog : public NaturalElement<Fog> {
public:
    Fog(float x, float y, float speed, float alpha, float width, float height);
    void update(float dt) override;
    void draw(const ScenePalette& palette) const override;

    void reset(int width);

private:
    float speed;
    float alpha;
    float height;
    float width;
};