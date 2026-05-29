#pragma once

#include <raylib.h>

// Base class for natural scene elements such as trees and raindrops.
// The template parameter is used to create a reusable NaturalElement base
// while still allowing derived types to be named naturally.
template <typename Derived>
class NaturalElement {
protected:
    Vector2 position;
    Color color;

public:
    NaturalElement(float x = 0.0f, float y = 0.0f, Color color = WHITE)
        : position{x, y}, color(color) {}

    virtual ~NaturalElement() = default;

    virtual void update(float dt) { (void)dt; }
    virtual void draw() const = 0;

    Vector2 getPosition() const { return position; }
    void setPosition(float x, float y) { position.x = x; position.y = y; }

    Color getColor() const { return color; }
    void setColor(Color newColor) { color = newColor; }
};
