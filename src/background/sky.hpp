#pragma once
#include <vector>
#include <raylib.h>

class Sky {
public:
    Sky(float start_height, Color color_bottom, Color color_top);
    void draw() const;

private:
    float start_height;
    Color color_bottom;
    Color color_top;
};