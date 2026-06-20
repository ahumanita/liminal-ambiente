#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>

#include "natural_element.hpp"

namespace liminal {

class Tree : public NaturalElement {
public:
    Tree(float x, float y, float scale = 1.0f, uint8_t crownColorIndex = 0, uint8_t trunkColorIndex = 0);
    float getScale() const {return scale;}
    uint8_t getTrunkColorIndex() const {return trunkColorIndex;}

private:
    float scale;
    uint8_t trunkColorIndex;
};

class Forest {
public:
    Forest(int lowerX, int upperX, int lowerY, int upperY, float density);
    std::vector<Tree> getTrees() const {return trees;}

private:    
    std::vector<Tree> trees;
    int lowerX;
    int upperX;
    int lowerY;
    int upperY;
    float density;   
};

} // namespace liminal