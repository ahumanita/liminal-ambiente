#pragma once
#include <raylib.h>
#include <vector>
#include <algorithm>
#include "natural_element.hpp"

class Tree : public NaturalElement<Tree> {
public:
    Tree(float x, float y, float scale = 1.0f, Color foliageColor = {34, 139, 34, 255}, float shadeFactor = 0.0f);
    void draw() const override;

private:
    float scale;
    float shadeFactor; // Optional: could be used to vary the color of the tree for depth effect
};

class Forest {
public:
    Forest(int lowerX, int upperX, int lowerY, int upperY, float density);
    void draw() const;

private:    
    std::vector<Tree> trees;
    int lowerX;
    int upperX;
    int lowerY;
    int upperY;
    float density;   
};