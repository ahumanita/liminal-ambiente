#include "fog.hpp"
#include "procedural/random.hpp"
#include "color_palettes/color_structs.hpp"

#include <algorithm>

namespace liminal {

namespace {

// Pick the fog bank's color index from its seed, so the same config always gives the same fog
uint8_t randomFogColorIndex(std::uint32_t seed) {
    Rng rng(seed);
    return static_cast<uint8_t>(randomInt(rng, 0, static_cast<int>(kColorRampSize) - 1));
}

} // namespace

Fog::Fog(const FogConfig& fogConfig)
    : NaturalElement(fogConfig.x, fogConfig.y, randomFogColorIndex(fogConfig.seed)), config(fogConfig) {}

void Fog::update(float dt) {
    position.x = position.x + config.speed * dt;
}

void Fog::setSpeed(float newSpeed) {
    config.speed = newSpeed;
}

void Fog::setAlpha(float newAlpha) {
    config.density = std::clamp(newAlpha, 0.0f, 1.0f);
}

} // namespace liminal
