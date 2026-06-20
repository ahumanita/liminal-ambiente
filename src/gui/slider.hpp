#pragma once
#include <vector>
#include <raylib.h>

// only include window properties if not already defined
#ifndef WINDOW_PROPERTIES_HPP_
#define WINDOW_PROPERTIES_HPP_
    #include "gui/window_properties.hpp"
#endif

namespace liminal {

class Slider {
public:
    Slider(float x, float y, float width, float height, float& valueRef, const char* labelStr) noexcept;

    void update(const Vector2& mousePos, bool isMouseDown);
    void draw(WindowProperties windowProps) const;
    void setValue(float newValue);
    float getValue() const;

private:
    Rectangle sliderRect;
    float& value; // Normalized value between 0.0 and 1.0
    char label[32];
    bool isDragging;
};

} // namespace liminal