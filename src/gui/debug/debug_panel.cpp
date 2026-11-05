#include "debug_panel.hpp"

#include <algorithm>
#include <string>

namespace liminal {

namespace {

const int kTabHeight = 28;
const int kRowHeight = 36;
const int kPadding = 14;

} // namespace

DebugPanel::DebugPanel(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {
    categories.push_back("Environment");
    parametersByCategory.emplace_back();
}

void DebugPanel::addFloatParameter(const std::string& category, const std::string& label, float& value, float minValue, float maxValue) {
    int categoryIndex = -1;
    for (size_t i = 0; i < categories.size(); ++i) {
        if (categories[i] == category) {
            categoryIndex = static_cast<int>(i);
            break;
        }
    }

    if (categoryIndex == -1) {
        categories.push_back(category);
        parametersByCategory.emplace_back();
        categoryIndex = static_cast<int>(categories.size() - 1);
    }

    DebugParameter parameter;
    parameter.label = label;
    parameter.targetValue = &value;
    parameter.previewValue = value;
    parameter.minValue = minValue;
    parameter.maxValue = maxValue;
    parameter.trackRect = {0.0f, 0.0f, 0.0f, 0.0f};
    parametersByCategory[static_cast<size_t>(categoryIndex)].push_back(parameter);
    refreshLayout();
}

void DebugPanel::refreshLayout() {
    const float categoryAreaWidth = width - 2.0f * kPadding;
    const float tabWidth = categoryAreaWidth / static_cast<float>(std::max<size_t>(1, categories.size()));

    for (size_t categoryIndex = 0; categoryIndex < categories.size(); ++categoryIndex) {
        std::vector<DebugParameter>& parameters = parametersByCategory[categoryIndex];
        for (size_t parameterIndex = 0; parameterIndex < parameters.size(); ++parameterIndex) {
            DebugParameter& parameter = parameters[parameterIndex];
            const float rowY = y + kTabHeight + 12.0f + static_cast<float>(parameterIndex) * kRowHeight;
            parameter.trackRect = {
                x + 12.0f,
                rowY + 14.0f,
                width - 24.0f,
                8.0f
            };
        }
    }

    (void)tabWidth;
}

void DebugPanel::update(const Vector2& mousePos, bool isMouseDown) {
    if (!isMouseDown && mouseWasDown) {
        commitPendingChanges();
    }
    mouseWasDown = isMouseDown;

    const float tabWidth = (width - 2.0f * kPadding) / static_cast<float>(std::max<size_t>(1, categories.size()));
    const Rectangle panelBounds = { x, y, width, height };

    if (CheckCollisionPointRec(mousePos, panelBounds)) {
        const float tabStartX = x + kPadding;
        for (size_t tabIndex = 0; tabIndex < categories.size(); ++tabIndex) {
            const Rectangle tabBounds = {
                tabStartX + static_cast<float>(tabIndex) * tabWidth,
                y + 4.0f,
                tabWidth,
                static_cast<float>(kTabHeight)
            };

            if (isMouseDown && CheckCollisionPointRec(mousePos, tabBounds)) {
                activeCategory = static_cast<int>(tabIndex);
                return;
            }
        }
    }

    std::vector<DebugParameter>& activeParameters = parametersByCategory[static_cast<size_t>(activeCategory)];
    for (auto& parameter : activeParameters) {
        const bool pointerInsideTrack = CheckCollisionPointRec(mousePos, parameter.trackRect);
        if (isMouseDown && (pointerInsideTrack || parameter.isDragging)) {
            parameter.isDragging = true;
            const float range = parameter.maxValue - parameter.minValue;
            const float xPos = std::clamp(mousePos.x, parameter.trackRect.x, parameter.trackRect.x + parameter.trackRect.width);
            const float t = (xPos - parameter.trackRect.x) / parameter.trackRect.width;
            const float clampedT = std::clamp(t, 0.0f, 1.0f);
            parameter.previewValue = parameter.minValue + clampedT * range;
            continue;
        }

        if (!isMouseDown) {
            parameter.isDragging = false;
        }
    }
}

void DebugPanel::commitPendingChanges() {
    for (auto& categoryParameters : parametersByCategory) {
        for (auto& parameter : categoryParameters) {
            if (parameter.targetValue != nullptr) {
                *parameter.targetValue = parameter.previewValue;
            }
            parameter.isDragging = false;
        }
    }
}

void DebugPanel::draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), Fade(BLACK, 0.72f));
    DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), LIGHTGRAY);

    const float tabWidth = (width - 2.0f * kPadding) / static_cast<float>(std::max<size_t>(1, categories.size()));
    const float tabStartX = x + kPadding;

    for (size_t tabIndex = 0; tabIndex < categories.size(); ++tabIndex) {
        const Rectangle tabBounds = {
            tabStartX + static_cast<float>(tabIndex) * tabWidth,
            y + 4.0f,
            tabWidth,
            static_cast<float>(kTabHeight)
        };

        const bool isActive = static_cast<int>(tabIndex) == activeCategory;
        DrawRectangleRec(tabBounds, isActive ? DARKGRAY : GRAY);
        DrawRectangleLinesEx(tabBounds, 1.0f, WHITE);
        DrawText(categories[tabIndex].c_str(), static_cast<int>(tabBounds.x + 10.0f), static_cast<int>(tabBounds.y + 7.0f), 12, WHITE);
    }

    const std::vector<DebugParameter>& activeParameters = parametersByCategory[static_cast<size_t>(activeCategory)];
    for (size_t parameterIndex = 0; parameterIndex < activeParameters.size(); ++parameterIndex) {
        const DebugParameter& parameter = activeParameters[parameterIndex];
        const float labelY = y + kTabHeight + 16.0f + static_cast<float>(parameterIndex) * kRowHeight;
        const float value = parameter.previewValue;

        DrawText(parameter.label.c_str(), static_cast<int>(x + 18.0f), static_cast<int>(labelY), 12, WHITE);
        DrawText(TextFormat("%.3f", value), static_cast<int>(x + width - 60.0f), static_cast<int>(labelY), 12, WHITE);

        DrawRectangleRec(parameter.trackRect, DARKGRAY);
        const float normalized = (value - parameter.minValue) / std::max(parameter.maxValue - parameter.minValue, 0.0001f);
        const float knobX = parameter.trackRect.x + normalized * parameter.trackRect.width;
        DrawRectangle(static_cast<int>(knobX - 6.0f), static_cast<int>(parameter.trackRect.y - 4.0f), 12, 18, LIGHTGRAY);
        DrawRectangleLinesEx(parameter.trackRect, 1.0f, WHITE);
    }
}

} // namespace liminal
