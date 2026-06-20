#include <string.h>
#include <math.h> 

#include "slider.hpp"

using namespace liminal;

Slider::Slider(float x, float y, float width, float height, float& valueRef, const char* labelStr) noexcept
    : value(valueRef) {
        sliderRect = { x, y, width, height };
        strncpy(label, labelStr, sizeof(label) - 1);
        label[sizeof(label) - 1] = '\0';
    }

void Slider::draw(WindowProperties windowProps) const {
    DrawRectangleRec(sliderRect, DARKGRAY);
    float handleX = sliderRect.x + value * sliderRect.width;
    DrawRectangle(static_cast<int>(handleX - 6), static_cast<int>(sliderRect.y - 6), 12, 20, LIGHTGRAY);
    DrawText(TextFormat("%s: %.3f", label, value), 20, windowProps.height - 60, 12, WHITE);
}

void Slider::update(const Vector2& mousePos, bool isMouseDown) {
    if (isMouseDown && CheckCollisionPointRec(mousePos, sliderRect)) {
        float sliderT = (mousePos.x - sliderRect.x) / sliderRect.width;
        sliderT = fmaxf(0.0f, fminf(1.0f, sliderT));
        setValue(sliderT);
    }
}

void Slider::setValue(float newValue) {
    value = fmaxf(0.0f, fminf(1.0f, newValue));
}

float Slider::getValue() const {
    return value;
}