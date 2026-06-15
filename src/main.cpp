#include <iostream>
#include <raylib.h>
#include <cmath>
#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"
#include "background/mountains.hpp"
#include "color_palettes/palette_manager.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    WindowProperties windowProps(screenWidth, screenHeight, "Liminal Ambiente");

    const char *msg = "Hello World";
    const int fontSize = 24;

    PaletteManager paletteManager;
    EnvironmentState env{};
    env.timeOfDay = 0.5f;
    ScenePalette palette = paletteManager.computeCurrentPalette(env);
    float prevTime = env.timeOfDay;
    double lastPaletteUpdate = 0.0;
    const double paletteCooldown = 0.05; // seconds, recompute at most 20Hz while dragging

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Forest forest(50, screenWidth - 50, screenHeight - 140, screenHeight - 20, 0.0005f);
    Fog fog(0, 0.5*screenHeight, 75, 100, 0.5*screenWidth, screenHeight);
    Fog fog2(0, 0.25*screenHeight, 2, 50, 0.5*screenWidth, 0.75*screenHeight);
    // Create background
    Sky sky(0);
    Ground ground(120.0f);
    Mountains mountains(windowProps);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);
        fog.update(dt);
        fog2.update(dt);

        BeginDrawing();
        // Background
        sky.draw(palette);
        mountains.draw(palette);
        ground.draw(palette);

        // Natural elements
        // Draw a stylized tree at bottom center
        forest.draw(palette);
        // Draw rain
        rain.draw(palette);
        // Draw fog overlay
        fog.draw(palette);
        fog2.draw(palette);

        // UI text on top
        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (screenWidth - textWidth) / 2, 20, fontSize, WHITE);

        // Simple in-window slider to adjust timeOfDay for debugging
        Rectangle slider = { 20.0f, static_cast<float>(screenHeight - 40), 300.0f, 8.0f };
        DrawRectangleRec(slider, DARKGRAY);
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, slider)) {
            float t = (mouse.x - slider.x) / slider.width;
            t = fmaxf(0.0f, fminf(1.0f, t));
            env.timeOfDay = t;
        }
        float handleX = slider.x + env.timeOfDay * slider.width;
        DrawRectangle(static_cast<int>(handleX - 6), static_cast<int>(slider.y - 6), 12, 20, LIGHTGRAY);
        DrawText(TextFormat("timeOfDay: %.3f", env.timeOfDay), 20, screenHeight - 60, 12, WHITE);

        // Debounced recompute: update at most once per `paletteCooldown` while dragging,
        // but force an immediate update when the mouse button is released.
        double now = GetTime();
        bool timeChanged = fabsf(env.timeOfDay - prevTime) > 1e-4f;
        if (timeChanged && (now - lastPaletteUpdate) > paletteCooldown) {
            palette = paletteManager.computeCurrentPalette(env);
            prevTime = env.timeOfDay;
            lastPaletteUpdate = now;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && timeChanged) {
            palette = paletteManager.computeCurrentPalette(env);
            prevTime = env.timeOfDay;
            lastPaletteUpdate = now;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}