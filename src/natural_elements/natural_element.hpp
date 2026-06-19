#pragma once

#include "color_palettes/scene_palette.hpp"

#include <raylib.h>
#include <cstdint>

namespace liminal {

// Base class for natural scene elements such as trees and raindrops.
// The template parameter is used to create a reusable NaturalElement base
// while still allowing derived types to be named naturally.
class NaturalElement {
protected:
    Vector2 position;
    uint8_t colorPaletteIndex; // Index to select color from the palette for this element

public:
    NaturalElement(float x = 0.0f, float y = 0.0f, uint8_t colorPaletteIndex = 0)
        : position{x, y}, colorPaletteIndex(colorPaletteIndex) {}

    virtual ~NaturalElement() = default;

    virtual void update(float dt) { (void)dt; }
    virtual void draw(const ScenePalette &palette) const = 0;

    Vector2 getPosition() const { return position; }
    void setPosition(float x, float y) { position.x = x; position.y = y; }

    uint8_t getColorPaletteIndex() const { return colorPaletteIndex; }
    void setColorPaletteIndex(uint8_t newIndex) { colorPaletteIndex = newIndex; }
};

} // namespace liminal
