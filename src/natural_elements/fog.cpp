#include "fog.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

Fog::Fog(float x, float y, float speed, float alpha, float width, float height)
    : NaturalElement(x, y, static_cast<uint8_t>(GetRandomValue(0,7))), speed(speed), alpha(alpha), width(width), height(height) {}

void Fog::update(float dt) {
    position.x += speed * dt;
}

void Fog::reset(int width) {
    position.x = static_cast<float>(GetRandomValue(0, width));
    position.y = static_cast<float>(GetRandomValue(0, height));
}

} // namespace liminal