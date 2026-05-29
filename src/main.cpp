#include <iostream>
#include <raylib.h>
#include "natural_elements/rain.hpp"
#include "natural_elements/tree.hpp"
#include "natural_elements/fog.hpp"
#include "background/sky.hpp"
#include "background/ground.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    const char *msg = "Hello World";
    const int fontSize = 24;

    /* Dark blue rain (hex #00008B) */
    const Color DARK_BLUE = { 0, 0, 139, 255 };
    /* Pine green color (hex #01796F) */
    const Color PINE_GREEN = { 1, 121, 111, 255 };
    /* Light gray fog color with some transparency (hex #C8C8C8)*/
    const Color FOG_COLOR = { 200, 200, 200, 180 };

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight, DARK_BLUE);
    Forest forest(50, screenWidth - 50, screenHeight - 140, screenHeight - 20, 0.0005f);
    Fog fog(0, 0.5*screenHeight, 10, 100, 0.5*screenWidth, screenHeight, FOG_COLOR);
    Fog fog2(0, 0.25*screenHeight, 2, 50, 0.5*screenWidth, 0.75*screenHeight, FOG_COLOR);

    // Create background
    /* Sky from a rosy pink (hex #FDA6C1) to a light blue (hex #ADD8E6) */
    Sky sky(0, (Color){255, 182, 193, 255}, (Color){173, 216, 230, 255});
    /* Ground as dark green (hex #006400) */
    Ground ground(120.0f, (Color){0, 100, 0, 255});

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);
        fog.update(dt);
        fog2.update(dt);

        BeginDrawing();
        // Background
        sky.draw();
        ground.draw();

        // Natural elements
        // Draw a stylized tree at bottom center
        forest.draw();
        // Draw rain
        rain.draw();
        // Draw fog overlay
        fog.draw();
        fog2.draw();

        // UI text on top
        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (screenWidth - textWidth) / 2, 20, fontSize, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}