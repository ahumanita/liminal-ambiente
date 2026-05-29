#include "tree.hpp"
#include <raylib.h>
#include <iostream>

Tree::Tree(float x, float y, float scale, Color foliageColor, float shadeFactor)
    : NaturalElement<Tree>(x, y, foliageColor), scale(scale), shadeFactor(shadeFactor) {}

void Tree::draw() const {
    // Trunk
    int trunkW = static_cast<int>(16 * scale);
    int trunkH = static_cast<int>(40 * scale);
    // Draw trunk with a brown color and and scale brightness based on the shadeFactor
    Color trunkColor = (Color){101, 67, 33, 255};
    // Adjust color based on the shadeFactor
    trunkColor.r = static_cast<unsigned char>(trunkColor.r * (1.0f - shadeFactor));
    trunkColor.g = static_cast<unsigned char>(trunkColor.g * (1.0f - shadeFactor));
    trunkColor.b = static_cast<unsigned char>(trunkColor.b * (1.0f - shadeFactor));
    DrawRectangle(
        static_cast<int>(position.x - trunkW / 2),
        static_cast<int>(position.y),
        trunkW,
        trunkH,
        trunkColor
    );

    // Draw crown color with the specified foliage color and scale brightness based on a 
    // the shadeFactor
    Color crownColor = color;
    // Adjust color based on the shadeFactor
    crownColor.r = static_cast<unsigned char>(crownColor.r * (1.0f - shadeFactor));
    crownColor.g = static_cast<unsigned char>(crownColor.g * (1.0f - shadeFactor));
    crownColor.b = static_cast<unsigned char>(crownColor.b * (1.0f - shadeFactor));

    int s1 = static_cast<int>(80 * scale);
    int s2 = static_cast<int>(56 * scale);
    int s3 = static_cast<int>(40 * scale);

    Vector2 b1[3] = {
        {position.x - s1 / 2.0f, position.y},
        {position.x + s1 / 2.0f, position.y},
        {position.x, position.y - 48.0f * scale}
    };
    DrawTriangle(b1[0], b1[1], b1[2], crownColor);

    Vector2 b2[3] = {
        {position.x - s2 / 2.0f, position.y - 28.0f * scale},
        {position.x + s2 / 2.0f, position.y - 28.0f * scale},
        {position.x, position.y - 80.0f * scale}
    };
    DrawTriangle(b2[0], b2[1], b2[2], crownColor);

    Vector2 b3[3] = {
        {position.x - s3 / 2.0f, position.y - 52.0f * scale},
        {position.x + s3 / 2.0f, position.y - 52.0f * scale},
        {position.x, position.y - 108.0f * scale}
    };
    DrawTriangle(b3[0], b3[1], b3[2], crownColor);
}


Forest::Forest(int lowerX, int upperX, int lowerY, int upperY, float density)
    : lowerX(lowerX), upperX(upperX), lowerY(lowerY), upperY(upperY), density(density) {
    // Derive number of trees to place randomly based on density, area size and average tree width
    int area = (upperX - lowerX) * (upperY - lowerY);
    int treeCount = static_cast<int>(area * density / 2); // Assuming average tree occupies 80x80 area
    std::cout << treeCount << " trees will be generated in the forest." << std::endl;
    trees.reserve(treeCount);

    // Initialize trees within the specified area
    for (int i = 0; i < treeCount; ++i) {
        float x = static_cast<float>(GetRandomValue(lowerX, upperX));
        float y = static_cast<float>(GetRandomValue(lowerY, upperY));
        float scale = static_cast<float>(GetRandomValue(5, 15)) / 10.0f; // Random scale between 0.5 and 1.5
        float shadeFactor = static_cast<float>(GetRandomValue(0, 50)) / 100.0f; // Random shade factor between 0 and 0.5
        Color PINE_GREEN = {1, 121, 111, 255};
        trees.emplace_back(x, y, scale, PINE_GREEN, shadeFactor);
    }

    // Sort trees such that those with higher y (lower on the screen) are drawn last, creating a simple depth effect
    std::sort(trees.begin(), trees.end(), [](const Tree &a, const Tree &b) {
        return a.getPosition().y < b.getPosition().y;
    });
}

void Forest::draw() const {
    for (const auto &tree : trees) {
        tree.draw();
    }
}