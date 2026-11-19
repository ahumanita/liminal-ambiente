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
#include "gui/window_properties.hpp"
#include "scene/scene_size.hpp"
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
    // The window can be wider than the scene (debug panel); everything in the scene uses sceneSize
    WindowProperties windowProps(screenWidth, screenHeight, "Liminal Ambiente", fontSize);
    const SceneSize sceneSize{static_cast<float>(sceneWidth), static_cast<float>(sceneHeight)};
    InitWindow(windowProps.width, windowProps.height, windowProps.title);
    SetTargetFPS(60);

    // World state: time of day and weather (defaults in EnvironmentState)
    EnvironmentState env{};

    PaletteManager paletteManager(env);
    ScenePalette palette = paletteManager.computeCurrentPalette(env);

    // Create scene elements
    RainSystem rain(sceneWidth, sceneHeight);
    Forest forest;
    Fog fog;
    // Create background
    Sky sky;
    Ground ground;
    Mountains mountains(sceneSize);

    Scene scene(mountains, sky, ground, rain, forest, fog);

#ifdef LIMINAL_DEBUG
    DebugPanel debugPanel(static_cast<float>(sceneWidth + 18.0f), 24.0f, 300.0f, 260.0f);
    debugPanel.addFloatParameter("Environment", "Time of Day", env.timeOfDay, 0.0f, 1.0f);
    debugPanel.addFloatParameter("Weather", "Rain Intensity", env.rainIntensity, 0.0f, 1.0f);
    debugPanel.addFloatParameter("Weather", "Fog Density", env.fogDensity, 0.0f, 1.0f);
    debugPanel.addFloatParameter("Weather", "Wind Speed", env.windSpeed, 0.0f, 8.0f);
#endif

    // Initialize renderer
    Renderer renderer = Renderer(sceneSize);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

#ifdef LIMINAL_DEBUG
        debugPanel.update(GetMousePosition(), IsMouseButtonDown(MOUSE_LEFT_BUTTON));
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            debugPanel.commitPendingChanges();
        }
#endif

        rain.update(dt, env);
        fog.update(dt, env);

        BeginDrawing();
        ClearBackground(BLACK);

#ifdef LIMINAL_DEBUG
        BeginScissorMode(0, 0, sceneWidth, screenHeight);
#endif
        renderer.render(scene, palette, env);
#ifdef LIMINAL_DEBUG
        EndScissorMode();
#endif

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