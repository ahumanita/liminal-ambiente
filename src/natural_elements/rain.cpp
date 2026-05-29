#include "rain.hpp"
#include <raylib.h>
#include <cstdlib>

RainDrop::RainDrop(float x, float y, float len, float speed, Color color)
    : NaturalElement<RainDrop>(x, y, color), len(len), speed(speed) {}

void RainDrop::update(float dt) {
    position.y += speed * dt;
}

void RainDrop::draw() const {
    Vector2 start = { position.x, position.y };
    Vector2 end = { position.x, position.y + len };
    DrawLineEx(start, end, 1.0f, color);
}

void RainDrop::reset(int width) {
    position.x = static_cast<float>(GetRandomValue(0, width));
    position.y = -len;
}

RainSystem::RainSystem(int count, int screenW, int screenH, Color dropColor)
    : width(screenW), height(screenH), color(dropColor) {
    drops.reserve(count);
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(GetRandomValue(0, width));
        float y = static_cast<float>(GetRandomValue(-height, height));
        float len = static_cast<float>(GetRandomValue(8, 24));
        float speed = static_cast<float>(GetRandomValue(200, 700));
        drops.emplace_back(x, y, len, speed, dropColor);
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

void RainSystem::draw() const {
    for (const auto &d : drops) {
        d.draw();
    }
}
