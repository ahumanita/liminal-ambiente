#pragma once
#include <raylib.h>
#include "natural_element.hpp"

class Tree : public NaturalElement<Tree> {
public:
    Tree(float x, float y, float scale = 1.0f, Color foliageColor = {34, 139, 34, 255});
    void draw() const override;

private:
    float scale;
};
