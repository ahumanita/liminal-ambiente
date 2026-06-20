#pragma once
#include <vector>
#include <raylib.h>
#include "natural_element.hpp"

namespace liminal {

class Fog : public NaturalElement {
public:
    Fog(float x, float y, float speed, float alpha, float width, float height);
    void update(float dt) override;
    void reset(int width);

    float getWidth() const {return width;}
    float getHeight() const {return height;}

private:
    float speed;
    float alpha;
    float height;
    float width;
};

} // namespace liminal