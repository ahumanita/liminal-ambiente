#include <iostream>
#include <raylib.h>
#include "rain.hpp"
#include "tree.hpp"
#include "fog.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    const char *msg = "Hello World";
    const int fontSize = 24;

    /* Pine green background color (hex #01796F) */
    const Color PINE_GREEN = { 1, 121, 111, 255 };
    /* Light gray fog color with some transparency (hex #C8C8C8)*/
    const Color FOG_COLOR = { 200, 200, 200, 180 };

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Tree tree(screenWidth / 2.0f, screenHeight - 120.0f, 1.0f);
    Fog fog(0, 0.5*screenHeight, 10, 100, 0.5*screenWidth, screenHeight, FOG_COLOR);
    Fog fog2(0, 0.25*screenHeight, 2, 100, 0.5*screenWidth, 0.75*screenHeight, FOG_COLOR);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);
        fog.update(dt);
        fog2.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw a stylized tree at bottom center
        tree.draw();

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