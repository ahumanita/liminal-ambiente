#include <iostream>
#include <raylib.h>
#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"
#include "color_palettes/palettes/dusk.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    const char *msg = "Hello World";
    const int fontSize = 24;

    const DuskPalette palette; 

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Forest forest(50, screenWidth - 50, screenHeight - 140, screenHeight - 20, 0.0005f);
    Fog fog(0, 0.5*screenHeight, 75, 100, 0.5*screenWidth, screenHeight);
    Fog fog2(0, 0.25*screenHeight, 2, 50, 0.5*screenWidth, 0.75*screenHeight);
    // Create background
    Sky sky(0);
    Ground ground(120.0f);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);
        fog.update(dt);
        fog2.update(dt);

        BeginDrawing();
        // Background
        sky.draw(palette);
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

        EndDrawing();
    }
    CloseWindow();
    return 0;
}