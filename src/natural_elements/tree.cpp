#include "tree.hpp"
#include "procedural/random.hpp"

namespace liminal {

Tree::Tree(float x, float y, float scale, uint8_t crownColorIndex, uint8_t trunkColorIndex)
    : NaturalElement(x, y, crownColorIndex), scale(scale), trunkColorIndex(trunkColorIndex) {}


Forest::Forest(const ForestConfig& forestConfig)
    : config(forestConfig) {
    // Derive number of trees to place randomly based on density and area size
    const float area = (config.maxX - config.minX) * (config.maxY - config.minY);
    const int treeCount = static_cast<int>(area * config.density / 2);
    trees.reserve(treeCount);

    // One seeded generator for the whole forest: the same config always gives the same forest
    Rng rng(config.seed);

    // Initialize trees within the specified area
    for (int i = 0; i < treeCount; ++i) {
        float x = randomFloat(rng, config.minX, config.maxX);
        float y = randomFloat(rng, config.minY, config.maxY);
        float scale = randomFloat(rng, config.minScale, config.maxScale);
        // Randomly select crown and trunk color indices for the tree from the palette
        uint8_t crownColorIndex = static_cast<uint8_t>(randomInt(rng, config.minColorIndex, config.maxColorIndex));
        uint8_t trunkColorIndex = static_cast<uint8_t>(randomInt(rng, config.minColorIndex, config.maxColorIndex));

        trees.emplace_back(x, y, scale, crownColorIndex, trunkColorIndex);
    }

    // Sort trees such that those with higher y (lower on the screen) are drawn last, creating a simple depth effect
    std::sort(trees.begin(), trees.end(), [](const Tree &a, const Tree &b) {
        return a.getPosition().y < b.getPosition().y;
    });
}

} // namespace liminal
