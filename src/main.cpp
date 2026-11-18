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
#include "gui/slider.hpp"
#ifdef LIMINAL_DEBUG
#include "gui/debug/debug_panel.hpp"
#endif
#include "renderer/renderer.hpp"

using namespace liminal;

int main() {
    const int sceneWidth = 800;
    const int sceneHeight = 600;
    const int debugPanelWidth = 340;
    int screenWidth = sceneWidth;
    const int screenHeight = sceneHeight;
    const int fontSize = 24;
#ifdef LIMINAL_DEBUG
    screenWidth += debugPanelWidth;
#endif
    WindowProperties windowProps(screenWidth, screenHeight, "Liminal Ambiente", fontSize);
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    const char *msg = "Hello World";
    
    EnvironmentState env{};
    env.timeOfDay = 0.5f;
    float rainIntensity = 1.0f;
    float fogDensity = 0.5f;
    float fogSpeed = 2.0f;

    PaletteManager paletteManager(env);
    ScenePalette palette = paletteManager.computeCurrentPalette(env);

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Forest forest(50, screenWidth - 50, screenHeight - 140, screenHeight - 20, 0.0005f);
    Fog fog(0, 0.25f * screenHeight, fogSpeed, fogDensity, 0.5f * screenWidth, 0.75f * screenHeight);
    // Create background
    Sky sky(0);
    Ground ground(120.0f);
    Mountains mountains(windowProps, palette);

    Scene scene(mountains, sky, ground, rain, forest, fog);

#ifdef LIMINAL_DEBUG
    DebugPanel debugPanel(static_cast<float>(sceneWidth + 18.0f), 24.0f, 300.0f, 260.0f);
    debugPanel.addFloatParameter("Environment", "Time of Day", env.timeOfDay, 0.0f, 1.0f);
    debugPanel.addFloatParameter("Weather", "Rain Intensity", rainIntensity, 0.0f, 3.0f);
    debugPanel.addFloatParameter("Weather", "Fog Density", fogDensity, 0.0f, 1.0f);
    debugPanel.addFloatParameter("Scene", "Fog Drift", fogSpeed, 0.0f, 8.0f);
#endif

    // Initialize renderer
    Renderer renderer = Renderer(windowProps);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

#ifdef LIMINAL_DEBUG
        debugPanel.update(GetMousePosition(), IsMouseButtonDown(MOUSE_LEFT_BUTTON));
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            debugPanel.commitPendingChanges();
        }
        rain.setIntensity(rainIntensity);
        fog.setAlpha(fogDensity);
        fog.setSpeed(fogSpeed);
#endif

        rain.update(dt);
        fog.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);

#ifdef LIMINAL_DEBUG
        BeginScissorMode(0, 0, sceneWidth, screenHeight);
#endif
        renderer.render(scene, palette);
#ifdef LIMINAL_DEBUG
        EndScissorMode();
#endif

        // UI text on top
        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (sceneWidth - textWidth) / 2, 20, fontSize, WHITE);

#ifdef LIMINAL_DEBUG
        debugPanel.draw();
#endif

        double now = GetTime();
#ifdef LIMINAL_DEBUG
        const bool paletteUpdated = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
#else
        const bool paletteUpdated = false;
#endif
        palette = paletteManager.updatePaletteIfNeeded(env, now, paletteUpdated);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}