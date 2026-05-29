#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"

class Fog : public NaturalElement<Fog> {
public:
    Fog(float x, float y, float speed, float alpha, float width, float height, Color color);
    void update(float dt) override;
    void draw() const override;

    void reset(int width);

private:
    float speed;
    float alpha;
    float height;
    float width;
};