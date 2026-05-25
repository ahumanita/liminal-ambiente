#include <iostream>
#include <raylib.h>
#include "rain.hpp"
#include "tree.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);

    const char *msg = "Hello World";
    const int fontSize = 24;

    /* Pine green background color (hex #01796F) */
    const Color PINE_GREEN = { 1, 121, 111, 255 };

    // Create scene elements
    RainSystem rain(300, screenWidth, screenHeight);
    Tree tree(screenWidth / 2.0f, screenHeight - 120.0f, 1.0f);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        rain.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw a stylized tree at bottom center
        tree.draw();

        // Draw rain
        rain.draw();

        // UI text on top
        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (screenWidth - textWidth) / 2, 20, fontSize, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}