#pragma once

#include "color_palettes/scene_palette.hpp"
#include "environment/environment_state.hpp"

#include <raylib.h>
#include <cstdint>

namespace liminal {

// Base class for natural scene elements such as trees and raindrops:
// a position and an index into the element's color ramp.
class NaturalElement {
protected:
    Vector2 position;
    uint8_t colorPaletteIndex; // Index to select color from the palette for this element

public:
    NaturalElement(float x = 0.0f, float y = 0.0f, uint8_t colorPaletteIndex = 0)
        : position{x, y}, colorPaletteIndex(colorPaletteIndex) {}

    virtual ~NaturalElement() = default;

    // Advance the element by dt seconds, reacting to the current world state (wind, rain, ...)
    virtual void update(float dt, const EnvironmentState& env) { (void)dt; (void)env; }

    Vector2 getPosition() const { return position; }
    void setPosition(float x, float y) { position.x = x; position.y = y; }

    uint8_t getColorPaletteIndex() const { return colorPaletteIndex; }
    void setColorPaletteIndex(uint8_t newIndex) { colorPaletteIndex = newIndex; }
};

} // namespace liminal
