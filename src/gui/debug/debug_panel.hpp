#pragma once

#include <string>
#include <vector>
#include <raylib.h>

namespace liminal {

struct DebugParameter {
    std::string label;
    float* targetValue;
    float previewValue;
    float minValue;
    float maxValue;
    Rectangle trackRect;
    bool isDragging = false;
};

class DebugPanel {
public:
    DebugPanel(float x, float y, float width, float height);

    void addFloatParameter(const std::string& category, const std::string& label, float& value, float minValue, float maxValue);
    void update(const Vector2& mousePos, bool isMouseDown);
    void commitPendingChanges();
    void draw() const;

private:
    void refreshLayout();

    float x;
    float y;
    float width;
    float height;
    std::vector<std::string> categories;
    std::vector<std::vector<DebugParameter>> parametersByCategory;
    int activeCategory = 0;
    bool mouseWasDown = false;
};

} // namespace liminal
