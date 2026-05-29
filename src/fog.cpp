#include "fog.hpp"
#include <raylib.h>
#include <cstdlib>

Fog::Fog(float x, float y, float speed, float alpha, float width, float height, Color color)
    : NaturalElement<Fog>(x, y, color), speed(speed), alpha(alpha), width(width), height(height) {}

void Fog::update(float dt) {
    position.x += speed * dt;
}

void Fog::draw() const {
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), (Color){color.r, color.g, color.b, static_cast<unsigned char>(alpha)});
}

void Fog::reset(int width) {
    position.x = static_cast<float>(GetRandomValue(0, width));
    position.y = static_cast<float>(GetRandomValue(0, height));
}
