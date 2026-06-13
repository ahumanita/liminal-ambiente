#include <raylib.h>
#include <vector>

#include "color_palettes/scene_palette.hpp"
#include "gui/window_properties.hpp"

class Mountains {
public:
    Mountains(WindowProperties* props);
    ~Mountains();

    void draw(ScenePalette& palette);

private:
    std::vector<Vector2> ridgeLine; // Ridge line points for mountain shapes
    WindowProperties* windowProps; // To access screen dimensions for drawing
};