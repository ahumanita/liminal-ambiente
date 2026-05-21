#include <iostream>
#include <raylib.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);
    
    const char *msg = "Hello World";
    const int fontSize = 24;

    /* Pine green background color (hex #01796F) */
    const Color PINE_GREEN = { 1, 121, 111, 255 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PINE_GREEN);

        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (screenWidth - textWidth) / 2, (screenHeight - fontSize) / 2, fontSize, BLACK);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}