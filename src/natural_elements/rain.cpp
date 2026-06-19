#include "rain.hpp"
#include <raylib.h>
#include <cstdlib>

namespace liminal {

RainDrop::RainDrop(float x, float y, float len, float speed, uint8_t colorIndex)
    : NaturalElement(x, y, colorIndex), len(len), speed(speed) {}

void RainDrop::update(float dt) {
    position.y += speed * dt;
}

void RainDrop::draw(const ScenePalette& palette) const {
    Vector2 start = { position.x, position.y };
    Vector2 end = { position.x, position.y + len };
    Color dropColor = getColorFromRamp(palette.rainRamp, colorPaletteIndex);
    DrawLineEx(start, end, 1.0f, dropColor);
}

void RainDrop::reset(int width) {
    position.x = static_cast<float>(GetRandomValue(0, width));
    position.y = -len;
}

RainSystem::RainSystem(int count, int screenW, int screenH)
    : width(screenW), height(screenH) {
    drops.reserve(count);
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(GetRandomValue(0, width));
        float y = static_cast<float>(GetRandomValue(-height, height));
        float len = static_cast<float>(GetRandomValue(8, 24));
        float speed = static_cast<float>(GetRandomValue(200, 700));
        uint8_t dropColorIndex = static_cast<uint8_t>(GetRandomValue(0, 7)); // Random color index for the drop
        drops.emplace_back(x, y, len, speed, dropColorIndex);
    }
}

void RainSystem::update(float dt) {
    for (auto &d : drops) {
        d.update(dt);
        if (d.getPosition().y > height) {
            d.reset(width);
        }
    }
}

void RainSystem::draw(const ScenePalette& palette) const {
    for (const auto &d : drops) {
        d.draw(palette);
    }
}

} // namespace liminal
