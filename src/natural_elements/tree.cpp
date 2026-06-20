#include "tree.hpp"

namespace liminal {

Tree::Tree(float x, float y, float scale, uint8_t crownColorIndex, uint8_t trunkColorIndex)
    : NaturalElement(x, y, crownColorIndex), scale(scale), trunkColorIndex(trunkColorIndex) {}


Forest::Forest(int lowerX, int upperX, int lowerY, int upperY, float density)
    : lowerX(lowerX), upperX(upperX), lowerY(lowerY), upperY(upperY), density(density) {
    // Derive number of trees to place randomly based on density, area size and average tree width
    int area = (upperX - lowerX) * (upperY - lowerY);
    int treeCount = static_cast<int>(area * density / 2); // Assuming average tree occupies 80x80 area
    trees.reserve(treeCount);

    // Initialize trees within the specified area
    for (int i = 0; i < treeCount; ++i) {
        float x = static_cast<float>(GetRandomValue(lowerX, upperX));
        float y = static_cast<float>(GetRandomValue(lowerY, upperY));
        float scale = static_cast<float>(GetRandomValue(5, 15)) / 10.0f; // Random scale between 0.5 and 1.5
        // Randomly select a crown color index for the tree from the palette
        uint8_t crownColorIndex = static_cast<uint8_t>(GetRandomValue(0, 7));
        uint8_t trunkColorIndex = static_cast<uint8_t>(GetRandomValue(0, 7));

        trees.emplace_back(x, y, scale, crownColorIndex, trunkColorIndex);
    }

    // Sort trees such that those with higher y (lower on the screen) are drawn last, creating a simple depth effect
    std::sort(trees.begin(), trees.end(), [](const Tree &a, const Tree &b) {
        return a.getPosition().y < b.getPosition().y;
    });
}

} // namespace liminal