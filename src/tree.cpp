#include "tree.hpp"
#include <raylib.h>

Tree::Tree(float x, float y, float scale, Color foliageColor)
    : NaturalElement<Tree>(x, y, foliageColor), scale(scale) {}

void Tree::draw() const {
    int trunkW = static_cast<int>(16 * scale);
    int trunkH = static_cast<int>(40 * scale);
    DrawRectangle(
        static_cast<int>(position.x - trunkW / 2),
        static_cast<int>(position.y),
        trunkW,
        trunkH,
        (Color){101, 67, 33, 255}
    );

    int s1 = static_cast<int>(80 * scale);
    int s2 = static_cast<int>(56 * scale);
    int s3 = static_cast<int>(40 * scale);

    Vector2 b1[3] = {
        {position.x - s1 / 2.0f, position.y},
        {position.x + s1 / 2.0f, position.y},
        {position.x, position.y - 48.0f * scale}
    };
    DrawTriangle(b1[0], b1[1], b1[2], color);

    Vector2 b2[3] = {
        {position.x - s2 / 2.0f, position.y - 28.0f * scale},
        {position.x + s2 / 2.0f, position.y - 28.0f * scale},
        {position.x, position.y - 80.0f * scale}
    };
    DrawTriangle(b2[0], b2[1], b2[2], color);

    Vector2 b3[3] = {
        {position.x - s3 / 2.0f, position.y - 52.0f * scale},
        {position.x + s3 / 2.0f, position.y - 52.0f * scale},
        {position.x, position.y - 108.0f * scale}
    };
    DrawTriangle(b3[0], b3[1], b3[2], color);
}
