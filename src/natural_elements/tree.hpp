#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>

#include "natural_element.hpp"

namespace liminal {

class Tree : public NaturalElement {
public:
    Tree(float x, float y, float scale = 1.0f, uint8_t crownColorIndex = 0, uint8_t trunkColorIndex = 0);
    void draw(const ScenePalette &palette) const override;

private:
    float scale;
    uint8_t trunkColorIndex;
};

class Forest {
public:
    Forest(int lowerX, int upperX, int lowerY, int upperY, float density);
    void draw(const ScenePalette &palette) const;

private:    
    std::vector<Tree> trees;
    int lowerX;
    int upperX;
    int lowerY;
    int upperY;
    float density;   
};

} // namespace liminal