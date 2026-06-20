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
#include "renderer/renderer.hpp"

using namespace liminal;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int fontSize = 24;
    WindowProperties windowProps(screenWidth, screenHeight, "Liminal Ambiente", fontSize);
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);    

    const char *msg = "Hello World";
    
    EnvironmentState env{};
    env.timeOfDay = 0.5f;

    PaletteManager paletteManager(env);
    ScenePalette palette = paletteManager.computeCurrentPalette(env);

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Forest forest(50, screenWidth - 50, screenHeight - 140, screenHeight - 20, 0.0005f);
    Fog fog(0, 0.5*screenHeight, 75, 100, 0.5*screenWidth, screenHeight);
    Fog fog2(0, 0.25*screenHeight, 2, 50, 0.5*screenWidth, 0.75*screenHeight);
    // Create background
    Sky sky(0);
    Ground ground(120.0f);
    Mountains mountains(windowProps, palette);

    Scene scene(mountains, sky, ground);

    // GUI elements
    Slider timeOfDaySlider(20, screenHeight - 40, 300, 8, env.timeOfDay, "Time of Day");

    // Initialize renderer
    Renderer renderer = Renderer(windowProps);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);
        fog.update(dt);
        fog2.update(dt);

        BeginDrawing();
   
        renderer.render(scene, palette);

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

        timeOfDaySlider.draw(windowProps);
        timeOfDaySlider.update(GetMousePosition(), IsMouseButtonDown(MOUSE_LEFT_BUTTON));

        double now = GetTime();
        palette = paletteManager.updatePaletteIfNeeded(env, now, IsMouseButtonReleased(MOUSE_LEFT_BUTTON));

        EndDrawing();
    }
    CloseWindow();
    return 0;
}