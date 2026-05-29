#pragma once
#include <vector>
#include <raylib.h>

class Ground {
public:
    Ground(float height, Color color);
    void draw() const;

private:
    float height;
    Color color;
};