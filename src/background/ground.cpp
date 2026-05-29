#include "ground.hpp"
#include <raylib.h>
#include <cstdlib>

Ground::Ground(float height, Color color)
    : height(height), color(color) {}

void Ground::draw() const {
    // Create a rectangle with the specified color
    DrawRectangle(0, GetScreenHeight() - height, GetScreenWidth(), height, color);
}