#include <iostream>
#include <raylib.h>
#include <vector>

struct RainDrop {
    Vector2 position;
    float speed;
    float length;
};


int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Liminal Ambiente");
    SetTargetFPS(60);
    
    const char *msg = "Hello World";
    const int fontSize = 24;

    /* Pine green background color (hex #01796F) */
    const Color PINE_GREEN = { 1, 121, 111, 255 };
    /* Light blue for rain drops (hex #ADD8E6) */
    const Color RAIN_BLUE = { 173, 216, 230, 255 }; 

    /* Create randomly positioned rain drops */
    std::vector<RainDrop> rainDrops;
    for (int i = 0; i < 100; ++i) {
        RainDrop drop;
        drop.position = { static_cast<float>(GetRandomValue(0, screenWidth)), static_cast<float>(GetRandomValue(-screenHeight, 0)) };
        drop.speed = static_cast<float>(GetRandomValue(200, 400)) / 100.0f; // Speed between 2.0 and 4.0
        drop.length = static_cast<float>(GetRandomValue(10, 20)); // Length between 10 and 20
        rainDrops.push_back(drop);
    }   

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PINE_GREEN);

        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg, (screenWidth - textWidth) / 2, (screenHeight - fontSize) / 2, fontSize, BLACK);

        // Update and draw rain drops
        for (auto &drop : rainDrops) {
            drop.position.y += drop.speed;
            if (drop.position.y > screenHeight) {
                drop.position.y = static_cast<float>(GetRandomValue(-screenHeight, 0));
                drop.position.x = static_cast<float>(GetRandomValue(0, screenWidth));
                drop.speed = static_cast<float>(GetRandomValue(200, 400)) / 100.0f;
                drop.length = static_cast<float>(GetRandomValue(10, 20));
            }
            DrawLine(drop.position.x, drop.position.y, drop.position.x, drop.position.y + drop.length, RAIN_BLUE);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}