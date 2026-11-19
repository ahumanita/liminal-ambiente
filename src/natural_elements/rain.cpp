#include "rain.hpp"
#include <algorithm>
#include <raylib.h>

namespace liminal {

RainDrop::RainDrop(float x, float y, float len, float speed, uint8_t colorIndex)
    : NaturalElement(x, y, colorIndex), len(len), speed(speed) {}

void RainDrop::update(float dt, const EnvironmentState& env) {
    (void)env; // The rain system already scales dt by the rain intensity
    position.y += speed * dt;
}

void RainDrop::reset(float newX) {
    position.x = newX;
    position.y = -len;
}

RainSystem::RainSystem(int screenW, int screenH, const RainConfig& rainConfig)
    : width(screenW), height(screenH), config(rainConfig), rng(rainConfig.seed) {
    drops.reserve(config.count);
    for (int i = 0; i < config.count; ++i) {
        float x = randomFloat(rng, 0.0f, static_cast<float>(width));
        float y = randomFloat(rng, static_cast<float>(-height), static_cast<float>(height));
        float len = randomFloat(rng, config.minLength, config.maxLength);
        float speed = randomFloat(rng, config.minSpeed, config.maxSpeed);
        uint8_t dropColorIndex = static_cast<uint8_t>(randomInt(rng, config.minColorIndex, config.maxColorIndex));
        drops.emplace_back(x, y, len, speed, dropColorIndex);
    }
}

void RainSystem::update(float dt, const EnvironmentState& env) {
    // Heavier rain makes the drops fall faster, up to the configured multiplier
    const float intensity = std::clamp(env.rainIntensity, 0.0f, 1.0f);
    const float adjustedDt = dt * intensity * config.maxSpeedMultiplier;
    for (auto &d : drops) {
        d.update(adjustedDt, env);
        if (d.getPosition().y > height) {
            d.reset(randomFloat(rng, 0.0f, static_cast<float>(width)));
        }
    }
}

} // namespace liminal
